#pragma once
#include "npc.h"

class Robber : public NPC {
public:
    Robber(const std::string& name, int x, int y);
    
    std::string GetType() const override;

    void accept(Visitor& visitor) override;

};