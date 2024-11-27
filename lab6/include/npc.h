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

    const std::string& GetName() const noexcept;
    int GetX() const noexcept;
    int GetY() const noexcept;
    virtual std::string GetType() const = 0;

    virtual void accept(Visitor& visitor) = 0;

};