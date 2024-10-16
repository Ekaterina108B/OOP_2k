#include <iostream>
#include "brackets.h"

bool main(){
    std::string expression;
    bool result;
    std::getline(std::cin, expression);
    result = ValidateTheExpression(expression);
    return result;
}
