#ifndef UNION_STACK_H
#define UNION_STACK_H

#include "Header.h"
#include "Stack_operations.h"

int union_stack() {

    system("cls");

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Stack stack1, stack2, stack3;
    init(&stack1);
    init(&stack2);
    init(&stack3);

    int size1, size2;
    printf("Введите размер первого стека: ");
    size1 = new_input_metod(INT_MIN, INT_MAX);
    input_increasing_Stack(&stack1, size1);

    printf("Введите размер второго стека: ");
    size2 = new_input_metod(INT_MIN, INT_MAX);
    input_increasing_Stack(&stack2, size2);

    mergeStacks(&stack1, &stack2, &stack3);

    printf("Вот объединенный стек : ");
    printStack(&stack3);

    return 0;
}

#endif