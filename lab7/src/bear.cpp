#include "bear.h"
#include "visitor.h"

Bear::Bear(const std::string& name, int x, int y) : NPC(name, x, y) {}

std::string Bear::GetType() const { return "Bear"; }
int Bear::GetMoveDistance() const { return MOVE_DISTANCE; }
int Bear::GetKillRange() const { return KILL_RANGE; }

void Bear::Accept(Visitor& visitor) { visitor.Visit(*this); }