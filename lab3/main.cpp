#include <memory>
#include "figure.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "array.h"

const size_t MAX_FIGURES = 100;

void Menu(void) {
    std::cout << std::endl;
    std::cout << "Выберите операцию:" << std::endl;
    std::cout << "1. Создать фигуру" << std::endl;
    std::cout << "2. Вывести информацию о всех фигурах" << std::endl;
    std::cout << "3. Удалить фигуру" << std::endl;
    std::cout << "4. Удалить все фигуры" << std::endl;
    std::cout << "5. Посчитать площадь всех фигур в массиве" << std::endl;
    std::cout << "0. Выход" << std::endl;
}

void Create_Figure(Array<Figure>& figures){
    int type;
    std::cout << "Выберите тип фигуры:\n1 - Прямоугольник,\n2 - Ромб,\n3 - Трапеция\n: ";
    std::cin >> type;

    if (type == 1){
        auto rectangle = std::make_unique<Rectangle>();
        std::cin >> *rectangle;
        figures.Add(std::move(rectangle));
    } else if (type == 2){
        auto rhombus = std::make_unique<Rhombus>();
        std::cin >> *rhombus;
        figures.Add(std::move(rhombus));
    } else if (type == 3){
        auto trapezoid = std::make_unique<Trapezoid>();
        std::cin >> *trapezoid;
        figures.Add(std::move(trapezoid));
    } else {
        std::cout << "Неверный тип фигуры." << std::endl;
    }
}

void Print_Figures(Array<Figure>& figures){
    if(figures.Size() == 0){
        std::cout << "Список фигур пуст." << std::endl;
        return;
    }
    
    std::cout << "\nИнформация о фигурах:\n";
    for (size_t i=0; i<figures.Size(); ++i) {
        Figure* fig = figures.Get(i);
        std::cout << "\nКоординаты вершин:\n" << *fig;
        auto center = fig->GetCenter();
        std::cout << "Геометрический центр: (" << center.x << ", " << center.y << ")\n";
        std::cout << "Площадь: " << static_cast<double>(*fig) << std::endl;
    }
}

void Delete_Figure(Array<Figure>& figures){
    size_t index = figures.Size();
    std::cout << "Введите номер фигуры для удаления: ";
    std::cin >> index;
    figures.Clear(index - 1);
}

void Delete_ALLFigures(Array<Figure>& figures){
    figures.ClearAll();
    Print_Figures(figures);
}

void Calculatoin_Area(Array<Figure>& figures){
    double area = 0;
    for (size_t i=0; i<figures.Size(); ++i){
        Figure* fig = figures.Get(i);
        area += static_cast<double>(*fig);
    }
    std::cout << "Общая лощадь: " << area << std::endl;
}

int main() {
    Array<Figure> figures(MAX_FIGURES);
    int choice;
    
    do {
        Menu();
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                Create_Figure(figures);
                break;
            case 2:
                Print_Figures(figures);
                break;
            case 3:
                Delete_Figure(figures);
                break;
            case 4:
                Delete_ALLFigures(figures);
                break;
            case 5:
                Calculatoin_Area(figures);
                break;
            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
        }

    } while (choice != 0);

    return 0;
}