#include "bear.h"
#include "visitor.h"

Bear::Bear(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Bear::GetType() const { return "Bear"; }

void Bear::accept(Visitor& visitor) {
    пока не знаю
}