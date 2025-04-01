#ifndef UNION_STACK_H
#define UNION_STACK_H

#include "Header.h"
#include "Stack_operations.h"

int union_stack() {

    system("cls");

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    struct Int_Node *stack_1 = NULL;
    struct Int_Node *stack_2 = NULL;
    struct Int_Node *stack_3 = NULL;

    int size1, size2;
    printf("������� ������ ������� �����: ");
    size1 = new_input_metod(0, INT_MAX);
    do {
        printf("\n������� ����  (�������� esc ��� ����������) :\n");
        inputIncreasingStack(&stack_1, size1);
    }while (isEmptyInt(stack_1));

    printf("\n������� ������ ������� �����: ");
    size2 = new_input_metod(0, INT_MAX);
    do {
        printf("\n������� ����  (�������� esc ��� ����������) :\n");
        inputIncreasingStack(&stack_2, size2);
    }while (isEmptyInt(stack_1));

    mergeStacks(stack_1, stack_2, &stack_3);

    printf("��� ������������ ���� : \n");
    printStackInt(stack_3);

    return 0;
}

#endif