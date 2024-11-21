#pragma once
#include <string>
#include <vector>

struct ComplexType {
    int id;
    double value;
    std::string name;
    std::vector<int> data;
    bool active;
    
    ComplexType() 
        : id(0), value(0.0), name(""), data(), active(false) {}
}; 