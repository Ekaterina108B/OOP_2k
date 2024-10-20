#include "seven.h"

Seven::Seven(){
    Array digits();
}
    
Seven::Seven(int number){
    if (number < 0){ throw std::invalid_argument("Number must be positive."); }

    size_t size = 0;
    int number_2 = number;
    while (number_2 != 0) {number_2 /= 7; ++size; }

    Array digits(size);
    size_t index = 0;
    while (number != 0) {
        digits.SetChar(index++, number%7);
        number /= 7;
    }
}

Seven Seven::operator+(const Seven &other){
    if (digits.GetSize() > other.digits.GetSize()) {
        Seven result(digits.GetSize() + 1);
    } else { Seven result(other.digits.GetSize() + 1); }

}