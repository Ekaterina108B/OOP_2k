#include "brackets.h"

int main(){
    std::string expression;
    bool result;
    std::getline(std::cin, expression);
    result = ValidateTheExpression(expression);
    if (result){ std::cout << "It's true\n"; }
    else { std::cout << "It's false\n"; }

    return 0;
}
