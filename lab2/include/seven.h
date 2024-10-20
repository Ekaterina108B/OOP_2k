#ifndef SEVEN_H
#define SEVEN_H

#include <iostream>
#include "array.h"

class Seven {
private:
    Array* digits;

public:
    Seven(void);
    Seven(int number);
    Seven operator+(const Seven &other);
};

#endif