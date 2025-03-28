#ifndef UNION_STACK_H
#define UNION_STACK_H

#include "Header.h"
#include "Stack_operations.h"

int union_stack() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Stack stack1, stack2, stack3;
    init(&stack1);
    init(&stack2);
    init(&stack3);

    int size1, size2;
    printf("¬ведите размер первого стека: ");
    size1 = new_input_metod(INT_MAX, INT_MIN);
    inputStack(&stack1, size1);

    printf("¬ведите размер второго стека: ");
    size2 = new_input_metod(INT_MAX, INT_MIN);
    inputStack(&stack2, size2);

    mergeStacks(&stack1, &stack2, &stack3);

    printf("ќбъединЄнный стек (по возрастанию): ");
    printStack(&stack3);

    return 0;
}

#endif
