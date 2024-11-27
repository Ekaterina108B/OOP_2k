#pragma once
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <algorithm>
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

    void NotifyObservers(const std::string& message);
    void WipeLogFile();

public:
    Game(const std::string& log_filename);
    virtual ~Game() = default;

    void AddNPC(const std::string& type, const std::string& name, int x, int y);
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    void PrintNPC() const;
    void RunBattle(int range);

    void AddObserver(std::shared_ptr<Observer> observer);
    size_t CountOfNPC() const noexcept;

};