#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(const std::string& message) = 0;
};

class FileObserver : public Observer {
private:
    std::string filename;

public:
    FileObserver(const std::string& filename);
    void Update(const std::string& message) override;
};

class ConsoleObserver : public Observer {
public:
    void Update(const std::string& message) override;
}; 