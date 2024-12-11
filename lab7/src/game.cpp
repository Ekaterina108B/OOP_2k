#include "game.h"

void Game::NotifyObservers(const std::string& message){
    for(auto& obs : observers){
        obs->Update(message);
    }
}

void Game::WipeLogFile() {
    std::ofstream log_file(log_filename, std::ofstream::out | std::ofstream::trunc);
    if (log_file.is_open()) {
        log_file.close();
    } else {
        std::cerr << "Unable to open log file: " << log_filename << std::endl;
    }
}

Game::Game(const std::string& log_filename) : factory(std::make_unique<ConcreteNPCFactory>()), log_filename(log_filename) {
    WipeLogFile();
}

void Game::AddNPC(const std::string& type, const std::string& name, int x, int y){
    if(x < 0 || x > MAP_SIZE || y < 0 || y > MAP_SIZE) { throw std::invalid_argument("Invalid coordinates"); }
    npcs.push_back(factory->CreateNPC(type, name, x, y));
}

void Game::SaveToFile(const std::string& filename) const {
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

void Game::LoadFromFile(const std::string& filename) {
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

void Game::PrintNPCs() const {
    for (const auto& npc : npcs) {
        std::cout << npc->GetType() << " " << npc->GetName() << " at (" << npc->GetX() << ", " << npc->GetY() << ")" << std::endl;
    }
}

void Game::AddObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

size_t Game::CountOfNPC() const noexcept { return npcs.size(); }

void Game::StartGame() {
    running = true;
    InitializeRandomNPCs();

    auto move_and_combat = MoveAndCombatCoroutine();
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

        move_and_combat.handle.resume();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if(move_and_combat.handle){
        move_and_combat.handle.destroy();
    }
    PrintSurvivors();
}

void Game::InitializeRandomNPCs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> pos(0, Game::MAP_SIZE);
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

void Game::PrintMap() const {
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

void Game::PrintSurvivors() const {
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

void Game::StopGame() {
    running = false;
}

Game::GameTask Game::MoveAndCombatCoroutine() {
    ConcreteVisitorBattle visitor;
    visitor.SetOnKillCallback([this](NPC* attacker, NPC* defender) {
        NotifyObservers(defender->GetType() + " " + defender->GetName() + 
                       " has been killed by " + attacker->GetType() + 
                       " " + attacker->GetName());
    });

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-1, 1);

    while (running) {
        {
            std::unique_lock<std::shared_mutex> lock(data_mutex);
            
            for (auto& npc : npcs) {
                if (!npc->IsAlive()) { continue; }
                
                int move_distance = npc->GetMoveDistance();
                npc->Move(dist(gen) * move_distance, dist(gen) * move_distance);
            }

            for (auto& attacker : npcs) {
                if (!attacker->IsAlive()) continue;
                
                std::vector<NPC*> potential_opponents;
                for (auto& defender : npcs) {
                    if (!defender->IsAlive() || attacker.get() == defender.get()) { continue; }
                    potential_opponents.push_back(defender.get());
                }
                
                if (!potential_opponents.empty()) {
                    visitor.SeeOpponents(potential_opponents);
                    attacker->Accept(visitor);
                }
            }
        }
        
        co_await std::suspend_always{};
    }
}

bool Game::IsRunning() const { return running; }