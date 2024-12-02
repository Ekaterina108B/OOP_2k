#pragma once
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include "npc.h"

class NPCFactory {
public:
    virtual ~NPCFactory() = default;
    virtual std::unique_ptr<NPC> CreateNPC(const std::string& type, const std::string& name, int x, int y) = 0;
    virtual std::unique_ptr<NPC> LoadNPC(const std::string& data) = 0;
};

class ConcreteNPCFactory : public NPCFactory {
public:
    std::unique_ptr<NPC> CreateNPC(const std::string& type, const std::string& name, int x, int y) override;
    std::unique_ptr<NPC> LoadNPC(const std::string& data) override;

};