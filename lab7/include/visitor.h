#pragma once
#include <vector>
#include <functional>
#include <cmath>
#include <random>
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
    std::vector<NPC*> opponents;
    std::function<void(NPC*, NPC*)> OnKill;

    void ProcessCombat(NPC* attacker, NPC* defender);

public:
    ConcreteVisitorBattle(int range);

    void Visit(Elf& elf) override;
    void Visit(Bear& bear) override;
    void Visit(Robber& robber) override;

    void SeeOpponents(const std::vector<NPC*>& npcs);
    void SetOnKillCallback(std::function<void(NPC*, NPC*)> callback);
    bool CanAttack(const NPC* attacker, const NPC* defender, double distance) const;

};