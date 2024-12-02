#pragma once
#include "npc.h"

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y);
    
    std::string GetType() const override;

    void accept(Visitor& visitor) override;

};