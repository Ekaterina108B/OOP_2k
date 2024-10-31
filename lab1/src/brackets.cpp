#include <iostream>
#include <string>
#include "brackets.h"

bool ValidateTheExpression(std::string input){
    if (input.size() > 100) { return false; }
    
    int count_of_opening_brackets = 0;

    for (size_t c = 0; c < input.size(); ++c){
        if (input[c] == '('){ ++count_of_opening_brackets; }
        else if (input[c] == ')') {--count_of_opening_brackets; }
        
        if (count_of_opening_brackets < 0){ return false; }
    }

    if (count_of_opening_brackets != 0){ return false; }
    return true;
}