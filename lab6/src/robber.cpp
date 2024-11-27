#include "robber.h"
#include "visitor.h"

Robber::Robber(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Robber::GetType() const { return "Robber"; }

void Robber::accept(Visitor& visitor) { visitor.Visit(*this); }