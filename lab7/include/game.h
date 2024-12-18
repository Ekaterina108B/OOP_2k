#pragma once
#include <vector>
#include <memory>
#include <string>
#include <atomic>
#include <shared_mutex>
#include <mutex>
#include <coroutine>
#include <future>
#include "npc.h"
#include "factory.h"
#include "observer.h"
#include "visitor.h"

class Game {
private:
    std::vector<std::unique_ptr<NPC>> npcs;
    std::unique_ptr<NPCFactory> factory;
    std::vector<std::shared_ptr<Observer>> observers;
    std::string log_filename;
    std::atomic<bool> running{false};
    mutable std::shared_mutex data_mutex;
    mutable std::mutex console_mutex;

    struct GameTask {
        struct promise_type {
            GameTask get_return_object() { return GameTask(std::coroutine_handle<promise_type>::from_promise(*this)); }
            std::suspend_never initial_suspend() { return {}; }
            std::suspend_never final_suspend() noexcept { return {}; }
            void return_void() {}
            void unhandled_exception() {}
        };
        GameTask(std::coroutine_handle<promise_type> h) : handle(h) {}
        std::coroutine_handle<promise_type> handle;
    };

    GameTask MoveAndCombatCoroutine();

    void DisplayThread();
    void InitializeRandomNPCs();
    void PrintMap() const;
    void PrintSurvivors() const;
    void NotifyObservers(const std::string& message);
    void WipeLogFile();

public:
    static constexpr int MAP_SIZE = 100;
    
    Game(const std::string& log_filename);
    virtual ~Game() = default;

    void AddNPC(const std::string& type, const std::string& name, int x, int y);
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    void PrintNPCs() const;
    void StartGame();
    void StopGame();
    bool IsRunning() const;

    void AddObserver(std::shared_ptr<Observer> observer);
    size_t CountOfNPC() const noexcept;

};