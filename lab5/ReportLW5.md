# Отчет по лабораторной работе № 5
## по курсу "Объектно-оринетированное программирование"

Студент группы М8О-208Б-23 Федорова Екатерина Васильевна

Работа выполнена 

1. **Тема**: Основы метапрограммирования
2. **Цель работы**:
- Изучение устройства коллекций в стандартной библиотеке
- Получение навыков в использовании концепции «итератор»
- Получение навыков в использовании концепции «аллокатор»
3. **Задание (вариант №3)**: 
- Реализовать наследник `std::pmr::memory_resource`, который реализует стратегию работы с памятью согласно варианта задания.
- `memory_resource` должен позволять периспользовать освобождаемую память (освобожденную ранее с помощью `do_deallocate`)
- `memory_resource` при уничтожении должен подчищать всю неосвобожденную ранее память
- Реализовать шаблонный контейнер согласно варианту задания, который использует созданный `memory_resource` через шаблон `std::pmr::polymorphic_allocator`.
- Реализовать итератор к созданному контейнеру. Итератор должен соответствовать `std::forward_iterator_tag`.
- Создать код, демонстрирующий работ контейнера с простыми (`int`) и сложными типами  (`struct` с несколькими полями).

Стратегия работы `memory_resource`: Фиксированный блок памяти (выделяется один раз), информация о выделенных блоках памяти хранится в `std::map`.

Вариант: Однонаправленный список.

4. **Идея, метод, алгоритм решения задачи**: В !!!! расположена краткая и сухая демонстрация работы программы.

`ComplexType`: Сложная структура для тестирования. Содержит уникальный идентификатор, численное значение, строку имени, динамический массив данных и флаг активности. Также определён один конструктор и операторы сравнения для сравнения объектов.

`Nodes`: Узел/элемент однонаправленного списка, хранящий данные и указатель на следующий элемент.

`class pmr_list`: Реализация однонаправленного списка. 

`MemoryResource`: Класс, ответственный за выделение и освобождение памяти. Реализует методы `do_allocate` и `do_deallocate`, которые обеспечивают выделение блока памяти с выравниванием и освобождение. Метод `PushFront` добавляет элементы в начало списка; метод `PushBack` добавляет элемент в конец списка; метод `InsertAfter` вставляет новый элемент после заданного узла; метод `PopFront` удаляет первый элемент списка; метод `PopBack` удаляет последний элемент списка; метод `EraseAfter` удаляет элемент после заданного; метод `Clear` очищает весь список, освобождая память.

6. **Протокол**: 
Запуск тестов:
```
moscow@moscow:~/Рабочий стол/OOP_2k/lab5/build$ make test
Running tests...
Test project /home/moscow/Рабочий стол/OOP_2k/lab5/build
    Start 1: lab5_test
1/2 Test #1: lab5_test ........................   Passed    0.00 sec
    Start 2: lab5_test+
2/2 Test #2: lab5_test+ .......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.01 sec
```

Отдельные запуски вручную:
```
moscow@moscow:~/Рабочий стол/OOP_2k/lab5/build$ ./lab5/OOP_5
Char list contents: b d a c 

Complex list contents:
id: 1, value: 1.1, name: one, data: [1, 2, 3], active: true
id: 3, value: 3.3, name: tri, data: [7, 8, 9], active: false
id: 2, value: 2.2, name: two, data: [4, 5, 6], active: false
```

7. **Замечания автора** по существу работы: -.
8. **Выводы**:  Выполнила относительно быстро, но на душе как-то пусто. В предыдущие лабы я вкладывала часть своей души с эмоциями, пусть далеко не всегда радостными, а тут... Чувствуется, что задание просто на отработку темы. Возможно, я устала. Лабораторная работа не вызвала уникальный ощущений, считаю её выполненной.