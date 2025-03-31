#ifndef UNION_STACK_H
#define UNION_STACK_H

#include "Header.h"
#include "Stack_operations.h"

int union_stack() {

    system("cls");

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    struct Node* stack_1;
    struct Node* stack_2;
    struct Node* stack_3;

    int size1, size2;
    printf("Введите размер первого стека: ");
    size1 = new_input_metod(0, INT_MAX);
    inputIncreasingStack(&stack_1, size1);

    printf("Введите размер второго стека: ");
    size2 = new_input_metod(0, INT_MAX);
    inputIncreasingStack(&stack_1, size2);

    mergeStacks(stack_1, stack_2, &stack_3);

    printf("Вот объединенный стек : ");
    printStack(stack_3);

    return 0;
}

#endif