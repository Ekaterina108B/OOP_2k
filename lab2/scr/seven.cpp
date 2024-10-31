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
        digits.SetChar(index++, static_cast<unsigned char>(number%7 + '0'));
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

Seven::Seven(const Seven &other) : digits(other.digits) {}

Seven Seven::operator+(const Seven &other){
    size_t max_size = std::max(digits.GetSize(), other.digits.GetSize()) +1;
    Seven result;
    result.digits = Array(max_size);

    int memory = 0;
    for (size_t i = 0; i < max_size; ++i){
        int first = i < digits.GetSize() ? static_cast<int>(digits.GetChar(i) - '0') : 0;
        int second = i < other.digits.GetSize() ? static_cast<int>(other.digits.GetChar(i) - '0') : 0;
        int third = first + second + memory;
        result.digits.SetChar(i, static_cast<unsigned char>(third%7 + '0'));
        memory = third/7;
    }
    if (result.digits.GetChar(result.digits.GetSize() - 1) == '0'){
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

    int memory = 0;
    for (size_t i=0; i<max_size; ++i){
        int first = i < digits.GetSize() ? static_cast<int>(digits.GetChar(i) - '0') : 0;
        int second = i < other.digits.GetSize() ? static_cast<int>(other.digits.GetChar(i) - '0') : 0;
        int third = 0;
        if ((first > second) || (first == second && memory == 0)){
            third = first - second - memory;
            memory = 0;
        } else {
            third = 7 + first - second - memory;
            memory = 1;
        }
        result.digits.SetChar(i, static_cast<unsigned char>(third + '0'));
    }
    if (memory == 1){
        result.digits = Array(1, '0');
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
    std::string number;

    if (digits.GetSize() == 0) { return "0"; }

    for (size_t i = digits.GetSize() - 1; i > 0; --i){
        std::string c(1, digits.GetChar(i));
        number += c;
    }
    std::string c(1, digits.GetChar(0));
    number += c;
    return number;
}