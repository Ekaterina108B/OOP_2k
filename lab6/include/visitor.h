#pragma once
#include <vector>
#include <cmath>
#include "npc.h"

class Elf;
class Bear;
class Robber;

class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void Visit(Elf& elf) = 0;
    virtual void Visit(Bear& bear) = 0;
    virtual void Visit(Robber& robber) = 0;

};

class ConcreteVisitorBattle : public Visitor {
private:
    int range;
    std::vector<NPC*> opponents;
    std::vector<NPC*> killed;

public:
    ConcreteVisitorBattle(int range);

    void Visit(Elf& elf) override;
    void Visit(Bear& bear) override;
    void Visit(Robber& robber) override;

    void SeeOpponents(const std::vector<NPC*>& npcs);
    std::vector<NPC*> GetKilled() const;

    bool inRange(const NPC& npc_1, const NPC& npc_2) const;

};