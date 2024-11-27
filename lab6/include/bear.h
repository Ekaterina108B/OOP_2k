#pragma once
#include "npc.h"

class Bear : public NPC {
public:
    Bear(const std::string& name, int x, int y);
    
    std::string GetType() const override;

    void accept(Visitor& visitor) override;

};