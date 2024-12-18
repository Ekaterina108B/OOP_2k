#include "game.h"
#include <iostream>
#include <stdexcept>

//не изменяю традициям писать интерфейс на русском, а программу на английском
void Menu() {
    std::cout << std::endl;
    std::cout << "--- Меню ---" << std::endl;
    std::cout << "1. Добавление NPCs" << std::endl;
    std::cout << "2. Загрузка из файла" << std::endl;
    std::cout << "3. Пуск битв" << std::endl;
    std::cout << "4. Сохранение игры" << std::endl;
    std::cout << "5. Вывод всех NPC" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
}

void MenuChoiceOfNPC() {
    std::cout << "Выберете, кого хотите добавить." << std::endl;
    std::cout << "1. Медведь" << std::endl;
    std::cout << "2. Эльф" << std::endl;
    std::cout << "3. Разбойник" << std::endl;
    std::cout << "Ваш выбор: ";
}

void AddNPC(Game& game) {
    int choice;
    size_t count_of_NPC = game.CountOfNPC();
    std::string name;
    int x, y;

    MenuChoiceOfNPC();
    std::cin >> choice;
    std::cout << "Введите координаты вида х y: ";
    std::cin >> x >> y;

    if(choice == 1){
        name = "Bear_" + std::to_string(count_of_NPC);
        game.AddNPC("Bear", name, x, y);
    } else if(choice == 2){
        name = "Elf_" + std::to_string(count_of_NPC);
        game.AddNPC("Elf", name, x, y);
    } else if(choice == 3){
        name = "Robber_" + std::to_string(count_of_NPC);
        game.AddNPC("Robber", name, x, y);
    } else {
        std::cout << "Неверный выбор." << std::endl;
    }
}

void LoadNPCFromFile(Game& game) {
    try {
        game.LoadFromFile("game_state.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error loading game state: " << e.what() << std::endl;
    }
}

void RunBattle(Game& game) {
    int range;
    std::cout << "Введите диапазон: ";
    std::cin >> range;
    if(range < 0){ range = -range; }
    game.RunBattle(range);
    game.PrintNPC();
}

void SaveGame(Game& game) {
    try {
        game.SaveToFile("game_state.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error saving game state: " << e.what() << std::endl;
    }
}


int main() {
    std::cout << "Инициализация игры";
    const std::string log_filename = "battle_log.txt";
    std::cout << ".";
    Game game(log_filename);
    std::cout << ".";
    game.AddObserver(std::make_shared<ConsoleObserver>());
    std::cout << ".";
    game.AddObserver(std::make_shared<FileObserver>(log_filename));
    std::cout << "Готово!" << std::endl;

    int choice;
    do {
        Menu();
        std::cin >> choice;
        
        switch (choice) {
        case 1:
            AddNPC(game);
            std::cout << "NPC добавлен." << std::endl;
            break;
        case 2:
            LoadNPCFromFile(game);
            std::cout << "Игра загружена." << std::endl;
            break;
        case 3:
            RunBattle(game);
            std::cout << "Конец батлов." << std::endl;
            break;
        case 4:
            SaveGame(game);
            std::cout << "Игра сохранена." << std::endl;
            break;
        case 5:
            game.PrintNPC();
            break;
        case 0:
            std::cout << "Выход из игры. До свидания!" << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
        }
    } while (choice != 0);

    return 0;
}