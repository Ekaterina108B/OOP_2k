#include "seven.h"

Seven::Seven() : digits(1) {}

Seven::Seven(int number){
    if (number < 0){ throw std::invalid_argument("Number must be positive."); }

    size_t size = 0;
    int number_2 = number;
    while (number_2 != 0) {number_2 /= 7; ++size; }

    digits = Array(size);
    size_t index = 0;
    while (number != 0) {
        digits.SetChar(index++, number%7);
        number /= 7;
    }
}

Seven::Seven(std::string number){
    if (!isValid(number)) {
            throw std::invalid_argument("Некорректное число в семиричной системе: " + number);
        }

    removeLeadingZeros(number);
    number = number.empty() ? "0" : number;
    digits = Array(number.size());

    size_t idx = digits.GetSize()-1;
    for (char c : number){
        digits.SetChar(idx--, static_cast<unsigned char>(c));
    }
}

Seven Seven::operator+(const Seven &other){
    size_t max_size = std::max(digits.GetSize(), other.digits.GetSize()) +1;
    Seven result;
    result.digits = Array(max_size);

    unsigned char memory = 0;
    for (size_t i = 0; i < max_size; ++i){
        unsigned char first = i < digits.GetSize() ? digits.GetChar(i) : 0;
        unsigned char second = i < other.digits.GetSize() ? other.digits.GetChar(i) : 0;
        unsigned char third = first + second + memory;
        result.digits.SetChar(i, third%7);
        memory = third/7;
    }
    if (result.digits.GetChar(result.digits.GetSize() - 1) == 0){
        Array new_digits(result.digits.GetSize() - 1);
        for (size_t i = 0; i < new_digits.GetSize(); ++i) {
            new_digits.SetChar(i, result.digits.GetChar(i));
        }
        result.digits = new_digits;
    }
    return result;
}

Seven Seven::operator-(const Seven &other){
    size_t max_size = std::max(digits.GetSize(), other.digits.GetSize());
    Seven result;
    result.digits = Array(max_size);

    unsigned char memory = 0;
    for (size_t i=0; i<max_size; ++i){
        unsigned char first = i < digits.GetSize() ? digits.GetChar(i) : 0;
        unsigned char second = i < other.digits.GetSize() ? other.digits.GetChar(i) : 0;
        unsigned char third = 0;
        if ((first > second) || (first == second && memory == 0)){
            third = first - second - memory;
            memory = 0;
        } else {
            third = 7 + first - second - memory;
            memory = 1;
        }
        result.digits.SetChar(i, third);
    }
    if (memory == 1){
        result.digits = Array(1);
    } else if (result.digits.GetChar(result.digits.GetSize() - 1) == 0){
        size_t new_size = result.digits.GetSize();
        while (new_size > 0 && result.digits.GetChar(new_size - 1) == 0) { --new_size; }
        Array new_digits(new_size);
        for (size_t i = 0; i < new_digits.GetSize(); ++i) {
            new_digits.SetChar(i, result.digits.GetChar(i));
        }
        result.digits = new_digits;
    }
    return result;
}

Seven& Seven::operator=(const Seven &other){
    if (this != &other) { digits = other.digits; }
    return *this;
}

bool Seven::operator<(const Seven &other) const {
    if (digits.GetSize() != other.digits.GetSize()) {
        return digits.GetSize() < other.digits.GetSize();
    }
    for (size_t i = digits.GetSize(); i > 0; --i) {
        if (digits.GetChar(i-1) != other.digits.GetChar(i-1)) {
            return digits.GetChar(i-1) < other.digits.GetChar(i-1);
        }
    }
    return false;
}

bool Seven::operator>(const Seven &other) const {
    return other < *this;
}

bool Seven::operator==(const Seven &other) const {
    if (!(other < *this) && !(other > *this)) { return true; }
    return false;
}

bool Seven::isValid(std::string number){
    for (char c : number){
        if (c < '0' || c > '6') { return false; }
    }
    return true;
}

void Seven::removeLeadingZeros(std::string number){
    size_t non_zero = number.find_first_not_of('0');
    number = (non_zero == std::string::npos) ? "0" : number.substr(non_zero);
}

std::string Seven::toStr(void) const {
    size_t size = digits.GetSize();
    std::string number;
    for (size_t i = 0; i<size; ++i){
        number[size - 1 - i] = static_cast<char>(digits.GetChar(i));
    }
    return number;
}