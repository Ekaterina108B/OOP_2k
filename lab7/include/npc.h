#pragma once
#include <string>

class Visitor;

class NPC {
protected:
    std::string name;
    int x;
    int y;
    bool alive = true;

public:
    static constexpr int MAP_SIZE = 100;
    
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    const std::string& GetName() const;
    int GetX() const;
    int GetY() const;
    virtual std::string GetType() const = 0;
    virtual int GetMoveDistance() const = 0;
    virtual int GetKillRange() const = 0;

    bool IsAlive() const;
    void SetAlive(bool state);
    void Move(int dx, int dy);

    virtual void Accept(Visitor& visitor) = 0;

};