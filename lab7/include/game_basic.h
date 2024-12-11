#pragma once
#include <vector>
#include <memory>
#include <string>
#include <atomic>
#include <shared_mutex>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
#include "npc.h"
#include "factory.h"
#include "observer.h"
#include "visitor.h"


class GameBasic {
private:
    struct CombatTask {
        NPC* attacker;
        NPC* defender;
    };
    
    std::queue<CombatTask> combat_tasks;
    std::mutex combat_queue_mutex;
    std::condition_variable combat_cond_var;
    
    std::vector<std::unique_ptr<NPC>> npcs;
    std::unique_ptr<NPCFactory> factory;
    std::vector<std::shared_ptr<Observer>> observers;
    std::string log_filename;
    std::atomic<bool> running{false};
    mutable std::shared_mutex data_mutex;
    mutable std::mutex console_mutex;
    
    std::thread movement_thread;
    std::thread combat_thread;
    
    void MovementFunction();
    void CombatFunction();
    void InitializeRandomNPCs();
    void PrintMap() const;
    void PrintSurvivors() const;
    int RollDice() const;
    bool CanAttack(const NPC* attacker, const NPC* defender, double distance) const;
    void NotifyObservers(const std::string& message);

public:
    static constexpr int MAP_SIZE = 100;
    
    GameBasic(const std::string& log_filename);
    ~GameBasic();

    void AddNPC(const std::string& type, const std::string& name, int x, int y);
    void StartGame();
    void StopGame();
    bool IsRunning() const;
    void AddObserver(std::shared_ptr<Observer> observer);
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    void PrintNPCs() const;

    size_t CountOfNPC() const noexcept;
    void WipeLogFile();   

}; 