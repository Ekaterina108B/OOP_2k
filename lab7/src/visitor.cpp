#include "visitor.h"
#include "elf.h"
#include "bear.h"
#include "robber.h"

ConcreteVisitorBattle::ConcreteVisitorBattle() {}

void ConcreteVisitorBattle::Visit(Elf& elf) {
    if(!elf.IsAlive()) { return; }
    for(auto& opponent : opponents){
        if(!opponent->IsAlive() || &elf == opponent) { continue; }
        
        int dx = elf.GetX() - opponent->GetX();
        int dy = elf.GetY() - opponent->GetY();
        double distance = std::sqrt(dx*dx + dy*dy);
        if(CanAttack(&elf, opponent, distance)){
            ProcessCombat(&elf, opponent);
        }
    }
}

void ConcreteVisitorBattle::Visit(Bear& bear) {
    if(!bear.IsAlive()) { return; }
    for(auto& opponent : opponents){
        if(!opponent->IsAlive() || &bear == opponent) { continue; }
        
        int dx = bear.GetX() - opponent->GetX();
        int dy = bear.GetY() - opponent->GetY();
        double distance = std::sqrt(dx*dx + dy*dy);
        if(CanAttack(&bear, opponent, distance)){
            ProcessCombat(&bear, opponent);
        }
    }
}

void ConcreteVisitorBattle::Visit(Robber& robber) {
    if(!robber.IsAlive()) { return; }
    for(auto& opponent : opponents){
        if(!opponent->IsAlive() || &robber == opponent) { continue; }
        
        int dx = robber.GetX() - opponent->GetX();
        int dy = robber.GetY() - opponent->GetY();
        double distance = std::sqrt(dx*dx + dy*dy);
        if(CanAttack(&robber, opponent, distance)){
            ProcessCombat(&robber, opponent);
        }
    }
}

void ConcreteVisitorBattle::SeeOpponents(const std::vector<NPC*>& npcs) { opponents = npcs; }

void ConcreteVisitorBattle::ProcessCombat(NPC* attacker, NPC* defender){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dice(1, 6);
    int attack_roll = dice(gen);
    int defense_roll = dice(gen);

    if(attack_roll > defense_roll){
        defender->SetAlive(false);
        if(OnKill) {
            OnKill(attacker, defender);
        }
    }
}

bool ConcreteVisitorBattle::CanAttack(const NPC* attacker, const NPC* defender, double distance) const {
    if(distance > attacker->GetKillRange()){ return false; }

    if(attacker->GetType() == "Bear" && defender->GetType() == "Elf"){ return true; }
    if(attacker->GetType() == "Elf" && defender->GetType() == "Robber") { return true; }
    if(attacker->GetType() == "Robber" && defender->GetType() == "Robber") { return true; }    
    
    return false;
}

void SetOnKillCallback(std::function<void(NPC*, NPC*)> callback){ OnKill = callback; }