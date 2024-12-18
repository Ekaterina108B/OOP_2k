# Отчет по лабораторной работе № 4
## по курсу "Объектно-оринетированное программирование"

Студент группы М8О-208Б-23 Федорова Екатерина Васильевна

Работа выполнена 

1. **Тема**: Основы метапрограммирования
2. **Цель работы**:
- Изучение основ работы с шаблонами (template) в С++;
- Изучение шаблонов умных указателей.
3. **Задание (вариант №19)**: 
Разработать шаблоны классов согласно варианту задания. Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат. Фигуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника (эти фигуры просто должны быть вписаны в круг). Для хранения координат фигур необходимо реализовать свой шаблон `template <class T> Point`, в качестве параметра шаблона должен быть тип для переменных координат. Проверку на то что тип `T` скалярный реализовать с помощью `concept`. Разработать классы согласно варианту задания, классы должны наследоваться от базового шаблонного класса `Figure<T>`, где `T` скалярный тип подставляющийся в `Point`. При этом сами точки должны хранится в виде умных указателей `std::unique_ptr<Point<T>>`. Все классы должны поддерживать набор общих методов из предыдущей лабораторной работы.

Создать программу, которая позволяет:
- Запрещается использовать сырые указатели.
- Вводить из стандартного ввода `std::cin` фигуры согласно варианту задания.
- Динамический массив должен быть сделан в виде шаблона (параметр шаблона – класс для хранения в массиве `template <class T> Array {…}`).
- Сохранять созданные фигуры в динамический массив (переиспользовать от предыдущей лабораторной работы) умных указатели на фигуру (`std::shared_ptr<T[]>`).
- Фигуры должны иметь переопределенные операции копирования, сравнения и приведение к типу `double` (вычисление площади).
- Вызывать для всего массива общие функции (1-3 см. выше). Т.е. распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
- Необходимо уметь вычислять общую площадь фигур в массиве.
- Удалять из массива фигуру по индексу.
- При увеличении емкости копирования должна использоваться операция перемещения (`move`) для элементов массива (при перемещении из массива меньшего размера в массив большего размера)
- Программа должна содержать примеры работы с шаблоном массива как для базового типа `Figure*` (например, проверить для `Array<Figure<int>*>`) так и для типов наследников, например `Square`(`Array<Square<int>>`).

Фигуры из варианта: Прямоугольник, Трапеция, Ромб.
4. **Идея, метод, алгоритм решения задачи**: Пользователю предлагается выбрать одно из нескольких действий:

1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход

В файле `array.h` реализован массив, который используется для хранения уникальных указателей на фигуры. В файле `figure.h` реализован родительский класс `Figure` с методами и операторами:
1. `virtual ~Figure()` - стандартный деструктор.
2. `Point<T> GetCenter() const { return CalculationCenter(); }` - вызов функции для получение координат центра точки фигуры.
3. `double GetArea() const { return CalculationArea(); }` - вызов функции для получения площади фигуры.
4. `void Reset()` - обнуление фигуры (удаление всех вершин).
5. `bool operator==(const Figure<T>& other) const { return IsEqual(other); }` - оператор, вызывающий функцию сравнения двух фигур. В наследуемых классах функция переопределяется.
6. `Figure& operator=(const Figure& other)` - присваивание копированием.
7. `Figure& operator=(Figure&& other) noexcept` - присваивание переносом.
8. `friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig)` - перегрузка оператора вывода в стандартный поток вывода std::cout координат вершин фигуры.
9. `friend std::istream& operator>>` - перегрузка оператора чтения из стандартного потока данных фигур, реализуется отдельно в каждом классе-потомке.
10. `virtual std::string GetName() const = 0;` - метод получения названия фигуры.
11. `virtual operator double() const { return GetArea(); }` - Вычисление площади фигуры через перегрузку оператора приведения к типу `double`.

Далее в файлах `rectangle.h`, `rhombus.h`, `trapezoid.h`, реализованы сами классы `Rectangle`, `Rhombus` и `Trapezoid`, которые наследуются от `Figure` с переопределением методов. В `main.cpp` расположен интерфейс для пользователя.

6. **Протокол**: 
Запуск тестов:
```
moscow@moscow:~/Рабочий стол/OOP_2k/lab4/build$ make test
Running tests...
Test project /home/moscow/Рабочий стол/OOP_2k/lab4/build
    Start 1: lab4_test
1/2 Test #1: lab4_test ........................   Passed    0.00 sec
    Start 2: lab4_test+
2/2 Test #2: lab4_test+ .......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.01 sec
```

Отдельные запуски вручную:
```
moscow@moscow:~/Рабочий стол/OOP_2k/lab4/build$ lab4/OOP_4

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 1

Выберите тип фигуры:
1 - Прямоугольник,
2 - Ромб,
3 - Трапеция
: 1
Введите через пробел координаты фигуры вида x y:
2 5 6 5 6 1 2 1

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 1

Выберите тип фигуры:
1 - Прямоугольник,
2 - Ромб,
3 - Трапеция
: 3
Введите через пробел координаты фигуры вида x y:
10 10 11 12 12 10 11 8

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 1

Выберите тип фигуры:
1 - Прямоугольник,
2 - Ромб,
3 - Трапеция
: 2
Введите через пробел координаты фигуры вида x y:
6 0 9 -2 12 0 9 2

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 2

Информация о фигурах:
Фигура №1 (Rectangle):
Координаты вершин: (2, 5) (6, 5) (6, 1) (2, 1) 
Геометрический центр: (4, 3)
Площадь: 16

Фигура №2 (Trapezoid):
Координаты вершин: (10, 10) (11, 12) (12, 10) (11, 8) 
Геометрический центр: (11, 10)
Площадь: 4

Фигура №3 (Rhombus):
Координаты вершин: (6, 0) (9, -2) (12, 0) (9, 2) 
Геометрический центр: (9, 0)
Площадь: 12


Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 5
Общая площадь: 32

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 3
Введите номер фигуры для удаления: 1
Фигура удалена

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 2

Информация о фигурах:
Фигура №1 (Trapezoid):
Координаты вершин: (10, 10) (11, 12) (12, 10) (11, 8) 
Геометрический центр: (11, 10)
Площадь: 4

Фигура №2 (Rhombus):
Координаты вершин: (6, 0) (9, -2) (12, 0) (9, 2) 
Геометрический центр: (9, 0)
Площадь: 12


Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 5
Общая площадь: 16

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 4
Список фигур пуст.

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 2
Список фигур пуст.

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 5
Общая площадь: 0

Выберите операцию:
1. Создать фигуру
2. Вывести информацию о всех фигурах
3. Удалить фигуру
4. Удалить все фигуры
5. Посчитать площадь всех фигур в массиве
0. Выход
Ваш выбор: 0
Выход из программы.
```

7. **Замечания автора** по существу работы: -.
8. **Выводы**:  Я намучилась с ними, зато сделала. Сделала! Улучшила Array, наконец нормально разобравшись в этими всякими шаблонами. Да, пришлось просить немного помощи, зато после неё всё пошло как по маслу. Ну... Почти, но явно лучше и приятнее. Думаю изменить немного лабораторную работу 3 до её сдачи, чтобы тоже навести чуть больше красоты. В целом, даже немного воодушевлена. Лабораторную работу считаю выполненной.