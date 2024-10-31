#ifndef SEVEN_H
#define SEVEN_H

#include <iostream>
#include "array.h"

class Seven {
private:
    Array digits;

public:
    Seven(void);
    Seven(int number);
    Seven(std::string number);
    Seven operator+(const Seven &other);
    Seven operator-(const Seven &other);
    Seven& operator=(const Seven &other);
    bool operator<(const Seven &other) const;
    bool operator>(const Seven &other) const;
    bool operator==(const Seven &other) const;

    bool isValid(std::string number);
    void removeLeadingZeros(std::string number);
    std::string toStr(void) const;
};

#endif