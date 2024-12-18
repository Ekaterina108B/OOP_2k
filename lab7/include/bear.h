#pragma once
#include "npc.h"

class Bear : public NPC {
public:
    static constexpr int MOVE_DISTANCE = 5;
    static constexpr int KILL_RANGE = 10;
    
    Bear(const std::string& name, int x, int y);
    
    std::string GetType() const override;
    int GetMoveDistance() const override;
    int GetKillRange() const override;

    void Accept(Visitor& visitor) override;

};