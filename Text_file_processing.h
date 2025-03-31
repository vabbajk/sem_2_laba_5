#ifndef PROCESS_EVALUATION_H
#define PROCESS_EVALUATION_H

#include <float.h>
#include <string.h>

#include "Stack_operations.h"

int char_in_line(char c, char* line) {

    while (*line != '\0') {
        if (*line == c) {return 1;}
        line++;
    }
    return 0;
}

int is_a_num(char c) {
    if (c >= '0' && c <= '9' || c == '.') {return 1;}
    return 0;
}

int get_priority(char operator) {
    switch (operator) {
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
        case '^':
            return 4;
        case '(':
            return 1;
    }
}

double apply_operator(double a, double b, char operator) {
    switch (operator) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b != 0){return a / b;}
            else{return NAN;}
        case '^':
            return pow(a, b);
    }
}

int convert_from_infix_to_postfix(char *infix, char *postfix) {
    struct Char_Node *current = NULL;
    char current_operand;
    char *postfix_ptr = postfix;
    int position = 0;
    int last_was_operator = 1;

    while (*infix != '\0') {
        if (*infix == ' ') {
        } else if (is_a_num(*infix) || (*infix == '-' && last_was_operator && (is_a_num(*(infix + 1)) || *(infix + 1) == '('))) {
            if (*infix == '-') {
                *postfix_ptr++ = *infix++;
            }
            while (is_a_num(*infix)) {
                *postfix_ptr++ = *infix++;
            }
            *postfix_ptr++ = ' ';
            last_was_operator = 0;
            continue;
        } else if (*infix == '(') {
            pushChar(&current, *infix);
            last_was_operator = 1;
        } else if (*infix == ')') {
            int has_open = 0;
            while (!isEmptyChar(current)) {
                current_operand = popChar(&current);
                if (current_operand == '(') {has_open = 1; break;}
                *postfix_ptr++ = current_operand;
                *postfix_ptr++ = ' ';
            }
            if (!has_open){
                printf("Error in position %d, has not enough <<(>>\n", position, *infix);
                return 1;
            }
            last_was_operator = 0;
        } else if (char_in_line(*infix, "-+*/^")) {
            while (!isEmptyChar(current) && get_priority(peekChar(current)) >= get_priority(*infix)) {
                *postfix_ptr++ = popChar(&current);
                *postfix_ptr++ = ' ';
            }
            pushChar(&current, *infix);
            last_was_operator = 1;
        } else {
            printf("Error in position %d, unknown symbol <<%c>> \n", position, *infix);
            return 1;
        }
        infix++;
        position++;
    }
    while (!isEmptyChar(current)) {
        *postfix_ptr++ = popChar(&current);
        *postfix_ptr++ = ' ';
    }
    *postfix_ptr = '\0';
    printf("%s\n", postfix);
    return 0;
}

int calculate_RPN(char *input, double *output) {
    struct Node* current = NULL;
    int is_num = 0, iter = 0;
    char buffer[30] = "";
    int last_was_operator = 1;

    while (*input != '\0') {
        if (is_a_num(*input) || *input == '.' || (*input == '-' && last_was_operator)) {
            if (iter < 29) {
                buffer[iter++] = *input;
                is_num = 1;
            }
            last_was_operator = 0;
        } else if (*input == ' ') {
            if (is_num) {
                buffer[iter] = '\0';
                double temp;
                sscanf(buffer, "%lf", &temp);
                push(&current, temp);
                iter = 0;
                is_num = 0;
            }
            last_was_operator = 0;
        } else if (char_in_line(*input, "+-/*^")) {
            if (is_num) {
                buffer[iter] = '\0';
                double temp;
                sscanf(buffer, "%lf", &temp);
                push(&current, temp);
                iter = 0;
                is_num = 0;
            }
            if (current == NULL || current->next == NULL) {
                printf("Error: Not enough operands for operator %c\n", *input);
                return 1;
            }
            double a = pop(&current);
            double b = pop(&current);
            if (*input == '^' && a < 0) {
                push(&current, pow(b, a));
            } else {
                push(&current, apply_operator(b, a, *input));
            }
            last_was_operator = 1;
        }
        input++;
    }
    if (current == NULL || current->next != NULL) {
        printf("Error: Invalid postfix expression\n");
        return 1;
    }
    *output = pop(&current);
    return 0;
}



double process_evaluation(char **str) {
    if (*str == NULL || **str == '\0') {
        return DBL_MAX;
    }

    char *postfix = malloc(strlen(*str) * 2);
    if (!postfix) {
        printf("Memory allocation failed\n");
        return DBL_MAX;
    }

    double result;
    if (convert_from_infix_to_postfix(*str, postfix) != 0) {
        free(postfix);
        return DBL_MAX;
    }

    if (calculate_RPN(postfix, &result) != 0) {
        free(postfix);
        return DBL_MAX;
    }

    free(postfix);
    return result;
}



#endif
