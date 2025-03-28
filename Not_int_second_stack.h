#ifndef NOT_INT_SECOND_STACK_H
#define NOT_INT_SECOND_STACK_H

#include "Stack_operations.h"
#include "Header.h"
#include <windows.h>

int not_int_second_stack()
{

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Stack stack1, stack2;
    init(&stack1);
    init(&stack2);

    int size1, size2;

    printf("¬ведите максимальный размер первого стека: ");
    size1 = new_input_metod(INT_MIN, INT_MAX);
    inputStack(&stack1, size1);

    printf("¬ведите максимальный размер второго стека: ");
    size2 = new_input_metod(INT_MAX, INT_MIN);
    inputStack(&stack2, size2);

    printUnique(&stack1, &stack2);

    return 0;
}

#endif
