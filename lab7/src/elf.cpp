#include "elf.h"
#include "visitor.h"

Elf::Elf(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Elf::GetType() const { return "Elf"; }

int Elf::GetMoveDistance() const { return MOVE_DISTANCE; }
int Elf::GetKillRange() const { return KILL_RANGE; }

void Elf::Accept(Visitor& visitor) { visitor.Visit(*this); }