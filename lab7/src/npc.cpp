#include "npc.h"

NPC::NPC(const std::string& name, int x, int y) : name(name), x(x), y(y) {}

const std::string& NPC::GetName() const { return name; }

int NPC::GetX() const { return x; }

int NPC::GetY() const { return y; }

bool NPC::IsAlive() const { return alive; }

void NPC::SetAlive(bool state) { alive = state; }

void NPC::Move(int dx, int dy) {
    int newX = x + dx;
    int newY = y + dy;
    x = std::max(0, std::min(newX, NPC::MAP_SIZE));
    y = std::max(0, std::min(newY, NPC::MAP_SIZE));
} 