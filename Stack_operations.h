#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    double data;
    struct Node* next;
};

struct Int_Node {
    double data;
    struct Int_Node* next;
};

struct Char_Node {
    char data;
    struct Char_Node* next;
};

struct Node* createNode(double data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error from createNode\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Char_Node* createCharNode(char data) {
    struct Char_Node* newNode = (struct Char_Node*)malloc(sizeof(struct Char_Node));
    if (!newNode) {
        printf("Memory allocation error from createCharNode\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Int_Node* createIntNode(int data) {
    struct Int_Node* newNode = (struct Int_Node*)malloc(sizeof(struct Int_Node));
    if (!newNode) {
        printf("Memory allocation error from createNode\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(struct Node** top, double data) {
    struct Node* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}

void pushChar(struct Char_Node** top, char data) {
    struct Char_Node* newNode = createCharNode(data);
    newNode->next = *top;
    *top = newNode;
}

void pushDouble(struct Int_Node** top, int data) {
    struct Int_Node* newNode = createIntNode(data);
    newNode->next = *top;
    *top = newNode;
}

double pop(struct Node** top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    struct Node* temp = *top;
    double popped = temp->data;
    *top = (*top)->next;
    free(temp);
    return popped;
}

char popChar(struct Char_Node** top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    struct Char_Node* temp = *top;
    char popped = temp->data;
    *top = (*top)->next;
    free(temp);
    return popped;
}

int popInt(struct Int_Node** top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    struct Int_Node* temp = *top;
    int popped = temp->data;
    *top = (*top)->next;
    free(temp);
    return popped;
}


int isEmpty(struct Node* top) {
    if (!top) return 1;
    else return 0;
}

int isEmptyChar(struct Char_Node* top) {
    if (!top) return 1;
    else return 0;
}

int isEmptyInt(struct Int_Node* top) {
    if (!top) return 1;
    else return 0;
}

double peek(struct Node* top) {
    if (!top) return NAN;
    else return top->data;
}

char peekChar(struct Char_Node* top) {
    if (!top) return NAN;
    else return top->data;
}

double peek(struct Node* top) {
    if (!top) return NAN;
    else return top->data;
}

int inputStack(struct Node ** top, int size) {
    int current_value = 0, iterator = 0;

    do {
        current_value = new_input_metod(0, INT_MAX);
        if (current_value!=INT_MIN){push(top, )}
    }while (current_value != INT_MIN && iterator < size);
}

int isInStack(struct Node *s, double value) {
    while (s->next != NULL) {
        if (s->data == value) return 1;
        s = s->next;
    }
    return 0;
}

void printNotInSecondStack(struct Node **s1, struct Node **s2) {
    printf("First stack elements, found in second stack: ");
    while (*s1 != NULL) {
        if (!isInStack(*s2, (*s1)->data)) {
            printf("%.0lf ", (*s1)->data);
        }
        *s1 = (*s1)->next;
    }
    printf("\n");
}

void inputIncreasingStack(struct Node ** top, int size) {
    int iter = 0, min_value = INT_MIN;
    while (iter < size && min_value != NAN) {
        min_value = new_input_metod(min_value, INT_MAX);
        if (min_value != NAN) {
            push(top, min_value);
        }
    }
}

void mergeStacks(struct Node *s1, struct Node  *s2, struct Node **s3) {

    struct Node * tempStack;

    while (isEmpty(s1) || isEmpty(s2)) {
        if (isEmpty(s1)) {
            push(&tempStack, pop(&s2));
        } else if (isEmpty(s2)) {
            push(&tempStack, pop(&s1));
        } else if (peek(s1) > peek(s2)) {
            push(&tempStack, pop(&s1));
        } else {
            push(&tempStack, pop(&s2));
        }
    }

    while (!isEmpty(tempStack)) {
        push(s3, pop(&tempStack));
    }
}

void printStack(struct Node *top) {
    while (top->next != NULL) {
        printf("%lf ", top->data);
        top = top->next;
    }
    printf("%lf ", top->data);
}

#endif