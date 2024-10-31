#include <iostream>
#include "seven.h"

void Menu(void) {
    std::cout << std::endl;
    std::cout << "Выберите операцию:\n";
    std::cout << "1. Сложение\n";
    std::cout << "2. Вычитание\n";
    std::cout << "3. Сравнение\n";
    std::cout << "4. Перевод\n";
    std::cout << "5. Выход\n";
}

void Addition(void) {
    std::string input;

    std::cout << "Введите первое семеричное число: ";
    std::cin >> input;
    Seven num1(input);

    std::cout << "Введите второе семеричное число: ";
    std::cin >> input;
    Seven num2(input);

    Seven result = num1 + num2;
    
    std::cout << "Результат сложения: " << result.toStr() << std::endl;
}

void Subtraction() {
    std::string input;

    std::cout << "Введите первое семеричное число: ";
    std::cin >> input;
    Seven num1(input);

    std::cout << "Введите второе семеричное число: ";
    std::cin >> input;
    Seven num2(input);

    Seven result = num1 - num2;
    std::cout << "Результат вычитания: " << result.toStr() << std::endl;
}

void Comparison() {
    std::string input;

    std::cout << "Введите первое семеричное число: ";
    std::cin >> input;
    Seven num1(input);

    std::cout << "Введите второе семеричное число: ";
    std::cin >> input;
    Seven num2(input);

    if (num1 == num2) {
        std::cout << "Числа равны." << std::endl;
    } else if (num1 < num2) {
        std::cout << "Первое число меньше второго." << std::endl;
    } else {
        std::cout << "Первое число больше второго." << std::endl;
    }
}

void Translation(void){
    int input;
    std::cout << "Введите десятичное число: ";
    std::cin >> input;
    Seven num(input);

    std::cout << "Соответствующее семиричное число: " << num.toStr() << std::endl;
}

int main() {
    int choice;

    do {
        Menu();
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                Addition();
                break;
            case 2:
                Subtraction();
                break;
            case 3:
                Comparison();
                break;
            case 4:
                Translation();
                break;
            case 5:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
        }

    } while (choice != 5);

    return 0;
}