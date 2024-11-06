# Отчет по лабораторной работе № 1
## по курсу "Объектно-оринетированное программирование"

Студент группы М8О-208Б-23 Федорова Екатерина Васильевна

Работа выполнена 

1. **Тема**: Классы
2. **Цель работы**:
- Закрепление навыков работы с классами
- Закрепление навыков работы с динамической памятью на «куче»
- Закрепление навыков работы с массивами
3. **Задание (вариант №8)**: Создать класс Seven для работы с беззнаковыми целыми семеричными числами, используя для представления числа массив из элементов типа unsigned char, каждый элемент которого является семиричной цифрой. Младшая цифра имеет меньший индекс (единицы — в нулевом элементе массива). Используя в качестве образца класс Array, реализовать динамические контейнеры с
использованием динамического массива.
- Каждый класс должен быть разделен на интерфейс и реализацию.
- Самостоятельно определить необходимые типы, поля и дополнительные методы.
- Реализовать генерацию исключений в конструкторах и методах при необходимости (использовать
стандартные исключения).
- Реализовать арифметические операции: сложение, вычитание, копирование
- Реализовать операции сравнения: (больше, меньше, равно).
- Арифметические операции с присваиванием должны быть реализованы как методы класса.
4. **Идея, метод, алгоритм решения задачи**: Пользователю предлагается выбрать одно из нескольких действий:

1. Сложить два семиричных числа.
2. Вычесть из одного семиричного числа второе.
3. Сравнить два семиричный числа.
4. Перевести число из десятичной системы счисления в семиричную.
5. Завершить программу.

В файлах `array.h`  и `array.cpp` реализован динамический массив, который используется для представления числа в 7СС. В файлах `seven.h` и `seven.cpp` реализован сам класс `Seven` со всеми необходимыми методами и операторами:
1. `Seven(void);` - создание объекта без заданных параметров.
2. `Seven(int number);` - создание объекта на основе числа в 10СС. Перевод в 7СС осуществляется обычным способом деления и постепенного заполнения динамического массива.
3. `Seven(std::string number);` - создание объекта на основе строки, содержащей число в 7СС. Проверяет валидность ввода и осторожно преобразует типы.
4. `Seven(const Seven &other);` - глубокое копирование (ссылаться будут на разные массивы с одинаковыми значениями).
5. `Seven operator+(const Seven &other);` - оператор сложения. Находит максимальный размер из двух объектов и создаёт массив для третьего, размером на единицу больше. Поразрядно происходит сложение. Удаляется незначащий нуль.
6. `Seven operator-(const Seven &other);` - оператор вычитания. Находит максимальный размер из двух объектов и создаёт массив для третьего. Поразрядно происходит вычитание. Если во вспомогательной переменной, хранящей "перенос", значение не равно нулю, значит, из большего числа вычиталось меньшее, поэтому результату присваивается значение 0. В противном случае удаляются незначащие нули.
7. `Seven& operator=(const Seven &other);` - глубокое копирование.
8. `bool operator<(const Seven &other) const;` - оператор сравнения. Если размеры массивов одинаковые, то выводится значение `false`. Иначе происходит проверка поразрядная.
9. `bool operator>(const Seven &other) const;` - оператор сравнивания. Без комментариев.
10. `bool operator==(const Seven &other) const;` - оператор сравнивания. Без комментариев.
11. `bool isValid(std::string number);` - проверяет валидность строки, содержащей число в 7СС на лишние символы.
12. `void removeLeadingZeros(std::string number);` - метод очищения строки от незначащих нулей.
13. `std::string toStr(void) const;` - метод преобразования объекта в строчное представление.

6. **Протокол**: 
Запуск тестов:
```
moscow@moscow:~/Рабочий стол/OOP_2k/lab2/build$ make test
Running tests...
Test project /home/moscow/Рабочий стол/OOP_2k/lab2/build
    Start 1: test_lab2
1/2 Test #1: test_lab2 ........................   Passed    0.00 sec
    Start 2: test+_lab2
2/2 Test #2: test+_lab2 .......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.01 sec
```

Отдельные запуски вручную:
```
moscow@moscow:~/Рабочий стол/OOP_2k/lab2/build$ lab2/OOP_2

Выберите операцию:
1. Сложение
2. Вычитание
3. Сравнение
4. Перевод
5. Выход
Ваш выбор: 1
Введите первое семеричное число: 11
Введите второе семеричное число: 21
Результат сложения: 32

Выберите операцию:
1. Сложение
2. Вычитание
3. Сравнение
4. Перевод
5. Выход
Ваш выбор: 2
Введите первое семеричное число: 123
Введите второе семеричное число: 23
Результат вычитания: 100

Выберите операцию:
1. Сложение
2. Вычитание
3. Сравнение
4. Перевод
5. Выход
Ваш выбор: 3
Введите первое семеричное число: 13
Введите второе семеричное число: 24
Первое число меньше второго.

Выберите операцию:
1. Сложение
2. Вычитание
3. Сравнение
4. Перевод
5. Выход
Ваш выбор: 4
Введите десятичное число: 4587
Соответствующее семиричное число: 16242

Выберите операцию:
1. Сложение
2. Вычитание
3. Сравнение
4. Перевод
5. Выход
Ваш выбор: 5
Выход из программы.
```

7. **Замечания автора** по существу работы: можно добавить обратный перевод из 7СС в 10СС, тестов или арифмитических операций.
8. **Выводы**: Потихоньку стараюсь нагнать дедлайны или хотя бы не отстать ещё сильнее. В начале пришлось трудно из-за незнакомого синтаксиса, но по мере продвижения по задаче привыкла и набила руку. В ходе лабораторной работы я закрепила навыки работы с классами, с динамической памятью на «куче» и с массивами. Это задание далось тяжелее предыдущего, что неудивительно, однако не сломило моё упорство. 