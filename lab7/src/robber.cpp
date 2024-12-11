#include "robber.h"
#include "visitor.h"

Robber::Robber(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Robber::GetType() const { return "Robber"; }
int Robber::GetMoveDistance() const { return MOVE_DISTANCE; }
int Robber::GetKillRange() const { return KILL_RANGE; }

void Robber::Accept(Visitor& visitor) { visitor.Visit(*this); }