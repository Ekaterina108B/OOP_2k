#include "visitor.h"
#include "elf.h"
#include "bear.h"
#include "robber.h"

ConcreteVisitorBattle::ConcreteVisitorBattle(int range) : range(range) {}

void ConcreteVisitorBattle::Visit(Elf& elf) {
    for(auto& opponent : opponents){
        if (opponent != &elf && opponent->GetType() == "Robber" && inRange(elf, *opponent)){
            killed.push_back(opponent);
        }
    }
}

void ConcreteVisitorBattle::Visit(Bear& bear) {
    for(auto& opponent : opponents){
        if (opponent != &bear && opponent->GetType() == "Elf" && inRange(bear, *opponent)){
            killed.push_back(opponent);
        }
    }
}

void ConcreteVisitorBattle::Visit(Robber& robber) {
    for(auto& opponent : opponents){
        if (opponent != &robber && opponent->GetType() == "Robber" && inRange(robber, *opponent)){
            killed.push_back(opponent);
        }
    }
}

void ConcreteVisitorBattle::SeeOpponents(const std::vector<NPC*>& npcs) { opponents = npcs; }

std::vector<NPC*> ConcreteVisitorBattle::GetKilled() const { return killed; }

bool ConcreteBattleVisitor::inRange(const NPC& npc_1, const NPC& npc_2) const {
    int dx = npc_1.GetX() - npc_2.GetX();
    int dy = npc_1.GetY() - npc_2.GetY();
    return std::sqrt(dx*dx + dy*dy) <= range;
} 