#include "game_basic.h"

void GameBasic::NotifyObservers(const std::string& message){
    std::lock_guard<std::mutex> consoleLock(console_mutex);
    for(auto& obs : observers){
        obs->Update(message);
    }
}

void GameBasic::WipeLogFile() {
    std::ofstream log_file(log_filename, std::ofstream::out | std::ofstream::trunc);
    if (log_file.is_open()) {
        log_file.close();
    } else {
        std::cerr << "Unable to open log file: " << log_filename << std::endl;
    }
}

GameBasic::GameBasic(const std::string& log_filename) : factory(std::make_unique<ConcreteNPCFactory>()), log_filename(log_filename) {
    WipeLogFile();
}

GameBasic::~GameBasic() {
    if (running) {
        StopGame();
    }
}

void GameBasic::AddNPC(const std::string& type, const std::string& name, int x, int y){
    if(x < 0 || x > MAP_SIZE || y < 0 || y > MAP_SIZE) { throw std::invalid_argument("Invalid coordinates"); }
    std::unique_lock<std::shared_mutex> lock(data_mutex);
    npcs.push_back(factory->CreateNPC(type, name, x, y));
}

void GameBasic::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& npc : npcs) {
            if(npc->IsAlive()){
                file << npc->GetType() << " " << npc->GetName() << " " << npc->GetX() << " " << npc->GetY() << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open save file: " << filename << std::endl;
    }
}

void GameBasic::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        npcs.clear();
        std::string line;
        while (std::getline(file, line)) {
            npcs.push_back(factory->LoadNPC(line));
        }
        file.close();
    } else {
        std::cerr << "Unable to open save file: " << filename << std::endl;
    }
}

void GameBasic::PrintNPCs() const {
    for (const auto& npc : npcs) {
        std::cout << npc->GetType() << " " << npc->GetName() << " at (" << npc->GetX() << ", " << npc->GetY() << ")" << std::endl;
    }
}

void GameBasic::AddObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

size_t GameBasic::CountOfNPC() const noexcept { return npcs.size(); }

void GameBasic::StartGame() {
    running = true;
    InitializeRandomNPCs();

    movement_thread = std::thread(&GameBasic::MovementFunction, this);
    combat_thread = std::thread(&GameBasic::CombatFunction, this);
    auto start_time = std::chrono::steady_clock::now();
    const auto game_duration = std::chrono::seconds(30);

    while(running) {
        auto current_time = std::chrono::steady_clock::now();
        if(current_time - start_time >= game_duration){
            running = false;
            break;
        }

        {
            std::lock_guard<std::mutex> console_lock(console_mutex);
            std::shared_lock<std::shared_mutex> data_lock(data_mutex);
            PrintMap();
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    combat_cond_var.notify_one();
    
    if (movement_thread.joinable()) { movement_thread.join(); }
    if (combat_thread.joinable()) { combat_thread.join(); }
    PrintSurvivors();
}

void GameBasic::MovementFunction() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-1, 1);
    ConcreteVisitorBattle visitor;
    
    while (running) {
        {
            std::unique_lock<std::shared_mutex> lock(data_mutex);
            
            for (auto& attacker : npcs) {
                if (!attacker->IsAlive()) continue;
                
                int move_distance = attacker->GetMoveDistance();
                attacker->Move(dist(gen) * move_distance, dist(gen) * move_distance);
                
                for (auto& defender : npcs) {
                    if (!defender->IsAlive() || attacker.get() == defender.get()) { continue; }
                    
                    std::lock_guard<std::mutex> queue_lock(combat_queue_mutex);
                    combat_tasks.push({attacker.get(), defender.get()});
                    combat_cond_var.notify_one();
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void GameBasic::CombatFunction() {
    ConcreteVisitorBattle visitor;
    visitor.SetOnKillCallback([this](NPC* attacker, NPC* defender) {
        NotifyObservers(defender->GetType() + " " + defender->GetName() + 
                       " has been killed by " + attacker->GetType() + 
                       " " + attacker->GetName());
    });
    
    while (running) {
        CombatTask task;
        {
            std::unique_lock<std::mutex> lock(combat_queue_mutex);
            combat_cond_var.wait(lock, [this]() { 
                return !running || !combat_tasks.empty(); 
            });
            
            if (!running && combat_tasks.empty()) break;
            
            task = combat_tasks.front();
            combat_tasks.pop();
        }
        
        {
            std::unique_lock<std::shared_mutex> lock(data_mutex);
            std::vector<NPC*> combatants = {task.attacker, task.defender};
            visitor.SeeOpponents(combatants);
            task.attacker->Accept(visitor);
        }
    }
}

void GameBasic::InitializeRandomNPCs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> pos(0, GameBasic::MAP_SIZE);
    std::uniform_int_distribution<> type(0, 2);

    for(int i=0; i<50; ++i){
        std::string npc_type;
        switch (type(gen)){
            case 0: npc_type = "Elf"; break;
            case 1: npc_type = "Bear"; break;
            case 2: npc_type = "Robber"; break;
        }
        AddNPC(npc_type, "NPC_" + std::to_string(i), pos(gen), pos(gen));
    }
}

void GameBasic::PrintMap() const {
    std::cout << "\033[2J\033[H";
    std::cout << std::string((MAP_SIZE + 1) * 2, '=') << std::endl;
    
    std::vector<std::vector<char>> map(MAP_SIZE + 1, 
        std::vector<char>(MAP_SIZE + 1, '.'));
    
    for(const auto& npc : npcs) {
        if(npc->IsAlive()) {
            map[npc->GetY()][npc->GetX()] = npc->GetType()[0];
        }
    }
    
    for(const auto& row : map) {
        for(char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
    
    std::cout << std::string((MAP_SIZE + 1) * 2, '=') << std::endl;
}

void GameBasic::PrintSurvivors() const {
    std::lock_guard<std::mutex> console_lock(console_mutex);
    std::shared_lock<std::shared_mutex> data_lock(data_mutex);
    
    std::cout << "\nSurviving NPCs:\n";
    for (const auto& npc : npcs) {
        if (npc->IsAlive()) {
            std::cout << npc->GetType() << " " << npc->GetName() 
                     << " at (" << npc->GetX() << ", " << npc->GetY() << ")\n";
        }
    }
}

void GameBasic::StopGame() {
    running = false;
}

bool GameBasic::IsRunning() const { return running; }