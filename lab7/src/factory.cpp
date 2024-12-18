#include "factory.h"
#include "bear.h"
#include "elf.h"
#include "robber.h"

std::unique_ptr<NPC> ConcreteNPCFactory::CreateNPC(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Elf"){ return std::make_unique<Elf>(name, x, y); }
    else if (type == "Bear"){ return std::make_unique<Bear>(name, x, y); }
    else if (type == "Robber"){ return std::make_unique<Robber>(name, x, y); }
    else { throw std::invalid_argument("Invalid NPC type"); }
}

std::unique_ptr<NPC> ConcreteNPCFactory::LoadNPC(const std::string& data) {
    std::istringstream iss(data);
    std::string type, name;
    int x, y;

    iss >> type >> name >> x >> y;
    return CreateNPC(type, name, x, y);
}