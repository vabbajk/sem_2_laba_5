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
    int data;
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

void pushInt(struct Int_Node** top, int data) {
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

int peekInt(struct Int_Node* top) {
    if (!top) return NAN;
    else return top->data;
}

int inputStack(struct Int_Node ** top, int size) {
    int current_value = INT_MIN, iterator = 0;

    do {

        current_value = new_input_metod(INT_MIN + 1, INT_MAX);
        if (current_value!=INT_MIN){pushInt(top, current_value);}
        iterator++;

    }while (current_value != INT_MIN && iterator < size);
    return 0;
}

int isInStack(struct Node *s, double value) {
    while (s!= NULL) {
        if (s->data == value) return 1;
        s = s->next;
    }
    return 0;
}

int isInStackInt(struct Int_Node *s, int value) {
    while (s != NULL) {
        if (s->data == value) return 1;
        s = s->next;
    }
    return 0;
}

void printNotInSecondStack(struct Int_Node *s1, struct Int_Node *s2) {
    printf("First stack elements, not found in second stack: ");
    struct Int_Node *temp = s1;
    while (temp != NULL) {
        if (!isInStackInt(s2, temp->data)) {
            printf("%d ", temp->data);
        }
        temp = temp->next;
    }
    printf("\n");
}

int inputIncreasingStack(struct Int_Node ** top, int size) {
    int current_value = INT_MIN, iterator = 0;

    do {

        current_value = new_input_metod(current_value, INT_MAX);
        if (current_value!=INT_MIN){pushInt(top, current_value);}
        iterator++;

    }while (current_value != INT_MIN && iterator < size);
    return 0;
}

void mergeStacks(struct Int_Node *s1, struct Int_Node *s2, struct Int_Node **s3) {
    struct Int_Node *tempStack = NULL;

    while (!isEmptyInt(s1) || !isEmptyInt(s2)) {
        if (isEmptyInt(s1)) {
            pushInt(&tempStack, popInt(&s2));
        } else if (isEmptyInt(s2)) {
            pushInt(&tempStack, popInt(&s1));
        } else if (peekInt(s1) > peekInt(s2)) {
            pushInt(&tempStack, popInt(&s1));
        } else {
            pushInt(&tempStack, popInt(&s2));
        }
    }

    while (!isEmptyInt(tempStack)) {
        pushInt(s3, popInt(&tempStack));
    }
}

void printStack(struct Node *top) {
    while (top->next != NULL) {
        printf("%lf ", top->data);
        top = top->next;
    }
    printf("%lf ", top->data);
}

void printStackInt(struct Int_Node *top) {
    while (top != NULL) {
        printf("%d \n", top->data);
        top = top->next;
    }
}
#endif