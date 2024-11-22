#include <iostream>

#include "memory_resource.h"
#include "pmr_list.h"
#include "complextype.h"

int main() {
    MemoryResource resource(1024 * 1024);
    
    pmr_list<char> char_list(&resource);
    char_list.PushFront('a');
    char_list.PushFront('b');
    char_list.PushBack('c');
    char_list.InsertAfter('b', 'd');
    std::cout << "Char list contents: ";
    for (const auto& value : char_list) {
        std::cout << value << " ";
    }
    std::cout << "\n";
    
    pmr_list<ComplexType> complex_list(&resource);
    ComplexType objectect_1;
    objectect_1.id = 1;
    objectect_1.value = 1.1;
    objectect_1.name = "one";
    objectect_1.data = {1, 2, 3};
    objectect_1.active = true;
    ComplexType objectect_2;
    objectect_2.id = 2;
    objectect_2.value = 2.2;
    objectect_2.name = "two";
    objectect_2.data = {4, 5, 6};
    objectect_2.active = false;
    ComplexType objectect_3;
    objectect_3.id = 3;
    objectect_3.value = 3.3;
    objectect_3.name = "tri";
    objectect_3.data = {7, 8, 9};
    objectect_3.active = false;
    complex_list.PushFront(objectect_1);
    complex_list.PushBack(objectect_2);
    complex_list.InsertAfter(objectect_1, objectect_3);
    std::cout << "\nComplex list contents:\n";
    for (const auto& object : complex_list) {
        std::cout << "id: " << object.id
                  << ", value: " << object.value
                  << ", name: " << object.name
                  << ", data: [";
        for (size_t i=0; i<object.data.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << object.data[i];
        }
        std::cout << "], active: " << (object.active ? "true" : "false") << "\n";
    }
    
    return 0;
} 