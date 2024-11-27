#include "elf.h"
#include "visitor.h"

Elf::Elf(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Elf::GetType() const { return "Elf"; }

void Elf::accept(Visitor& visitor) {
    пока не знаю
}