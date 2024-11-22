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
    bool operator==(const ComplexType &T){
        if ((this->id != T.id) || (this->value != T.value) || (this->name != T.name) || (this->data != T.data) || (this->active != T.active)){
            return false;
        }
        return true;
    }
    bool operator!=(const ComplexType &T){
        return !(*this == T);
    }
}; 