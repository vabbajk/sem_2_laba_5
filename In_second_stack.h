#ifndef In_second_stack_H
#define In_second_stack_H

#include "Stack_operations.h"
#include "Header.h"
#include <windows.h>

int in_second_stack()
{
    system("cls");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    struct Node *stack_1 = NULL;
    struct Node *stack_2 = NULL;

    int size1, size2;

    printf("\n¬ведите размер первого стека: ");
    size1 = new_input_metod(0, INT_MAX);
    inputStack(&stack_1, size1);


    printf("\n¬ведите размер второго стека: ");
    size2 = new_input_metod(0, INT_MAX);
    inputStack(&stack_2, size2);

    printNotInSecondStack(&stack_1, &stack_2);

    return 0;
}

#endif
