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

    struct Int_Node *stack_1 = NULL;
    struct Int_Node *stack_2 = NULL;

    int size1, size2;
    do {
        printf("\nВведите размер первого стека: ");
        size1 = new_input_metod(0, INT_MAX);
    } while (size1 <= 0);
    do {
        printf("\nВводите стек  (нажмиете esc для завершения) :\n");
        inputStack(&stack_1, size1);
    }while (isEmptyInt(stack_1));

    do {
        printf("\nВведите размер второго стека: ");
        size2 = new_input_metod(0, INT_MAX);
    } while (size2 <= 0);
    do{
    printf("\nВводите стек  (нажмиете esc для завершения) :\n");
    inputStack(&stack_2, size2);
    }while (isEmptyInt(stack_2));

    printNotInSecondStack(stack_1, stack_2);

    return 0;
}

#endif
