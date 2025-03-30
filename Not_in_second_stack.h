#ifndef NOT_IN_SECOND_STACK_H
#define NOT_IN_SECOND_STACK_H

#include "Stack_operations.h"
#include "Header.h"
#include <windows.h>

int not_int_second_stack()
{
    system("cls");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Stack stack1, stack2;
    init(&stack1);
    init(&stack2);

    int size1, size2;

    printf("\n¬ведите размер первого стека: ");
    size1 = new_input_metod(INT_MIN, INT_MAX);
    inputStack(&stack1, size1);

    printf("\n¬ведите размер второго стека: ");
    size2 = new_input_metod(INT_MIN, INT_MAX);
    inputStack(&stack2, size2);

    printUnique(&stack1, &stack2);

    return 0;
}

#endif
