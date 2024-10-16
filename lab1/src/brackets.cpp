#include <iostream>
#include "brackets.h"

bool ValidateTheExpression(void){
    char input;
    int count_of_opening_brackets = 0;

    std::cin >> input;
    while (input != '\n'){
        if (input == '('){ ++count_of_opening_brackets; }
        else if (input == ')') {--count_of_opening_brackets; }
        
        if (count_of_opening_brackets < 0){ return false; }
    }

    if (count_of_opening_brackets != 0){ return false; }
    return true;
}