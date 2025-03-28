#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include "stdio.h"
#include <windows.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, int value) {
    if (!isFull(s)) {
        s->data[++s->top] = value;
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top--];
    }
    return -1;  // ќшибка
}

int peek(Stack *s) {
    return isEmpty(s) ? -1 : s->data[s->top];
}

int isInStack(Stack *s, int value) {
    for (int i = 0; i <= s->top; i++) {
        if (s->data[i] == value) {
            return 1;
        }
    }
    return 0;
}

void inputStack(Stack *s, int size) {
    int value;
    printf("¬ведите элементы стека (-1 дл€ завершени€): \n");
    while (s->top < size - 1) {
        value = new_input_metod(INT_MAX, INT_MIN);
        if (value == -1) break;
        push(s, value);
    }
}

void printStack(Stack *s) {
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}


//////////////////////////////////////////////////////////////////////////////////

void printUnique(Stack *s1, Stack *s2) {
    printf("Ёлементы из первого стека, которых нет во втором: ");
    for (int i = 0; i <= s1->top; i++) {
        if (!isInStack(s2, s1->data[i])) {
            printf("%d ", s1->data[i]);
        }
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////

void mergeStacks(Stack *s1, Stack *s2, Stack *s3) {
    Stack tempStack;
    init(&tempStack);

    while (!isEmpty(s1) || !isEmpty(s2)) {
        if (isEmpty(s1)) {
            push(&tempStack, pop(s2));
        } else if (isEmpty(s2)) {
            push(&tempStack, pop(s1));
        } else if (peek(s1) > peek(s2)) {
            push(&tempStack, pop(s1));
        } else {
            push(&tempStack, pop(s2));
        }
    }

    while (!isEmpty(&tempStack)) {
        push(s3, pop(&tempStack));
    }
}

#endif
