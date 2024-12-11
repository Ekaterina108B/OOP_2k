#pragma once
#include <string>

class Visitor;

class NPC {
protected:
    std::string name;
    int x;
    int y;

public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    const std::string& GetName() const;
    int GetX() const;
    int GetY() const;
    virtual std::string GetType() const = 0;

    virtual void accept(Visitor& visitor) = 0;

};