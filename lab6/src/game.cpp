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
    if(x < 0 || x > 500 || y < 0 || y > 500) { throw std::invalid_argument("Invalid coordinates"); }
    npsc.push_back(factory->CreateNPC(type, name, x, y));
}

void Game::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& npc : npcs) {
            file << npc->GetType() << " " << npc->GetName() << " " << npc->GetX() << " " << npc->GetY() << std::endl;
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
            npcs.push_back(factory->loadNPC(line));
        }
        file.close();
    } else {
        std::cerr << "Unable to open save file: " << filename << std::endl;
    }
}

void Game::PrintNPC() const {
    for (const auto& npc : npcs) {
        std::cout << npc->GetType() << " " << npc->GetName() << " at (" << npc->GetX() << ", " << npc->GetY() << ")" << std::endl;
    }
}

void Game::RunBattle(int range) {
    ConcreteVisitorBattle visitor(range);
    std::vector<NPC*> npc_ptrs;
    for (auto& npc : npcs) {
        npc_ptrs.push_back(npc.get());
    }
    visitor.SeeOpponents(npc_ptrs);

    for (auto& npc : npcs) {
        npc->accept(visitor);
    }

    auto killed_NPC = visitor.GetKilled();

    std::sort(killed_NPC.begin(), killed_NPC.end());
    killed_NPC.erase(std::unique(killed_NPC.begin(), killed_NPC.end()), killed_NPC.end());

    for (auto killed : killed_NPC) {
        std::string message = killed->GetType() + " " + killed->GetName() + " has been killed";
        NotifyObservers(message);
    }

    for (auto it = npcs.begin(); it != npcs.end(); ) {
        if (std::find(killed_NPC.begin(), killed_NPC.end(), it->get()) != killed_NPC.end()) {
            it = npcs.erase(it);
        } else { ++it; }
    }
}

void Game::AddObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Game::CountOfNPC() const { return npcs.size()}