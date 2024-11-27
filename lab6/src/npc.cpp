#include "npc.h"

NPC::NPC(const std::string& name, int x, int y) : name(name), x(x), y(y) {}

const std::string& NPC::GetName() const { return name; }

int NPC::GetX() const { return x; }

int NPC::GetY() const { return y; }