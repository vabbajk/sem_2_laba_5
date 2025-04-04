#ifndef PROCESS_EVALUATION_H
#define PROCESS_EVALUATION_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <math.h>
#include "Stack_operations.h"


#define ERROR_UNKNOWN_SYMBOL 1
#define ERROR_UNMATCHED_PARENTHESIS 2
#define ERROR_DIVISION_BY_ZERO 3
#define ERROR_NOT_ENOUGH_OPERANDS 4
#define ERROR_INVALID_POSTFIX 5
#define ERROR_MEMORY_ALLOCATION 6

int char_in_line(char c, char* line) {
    while (*line != '\0') {
        if (*line == c) {
            return 1;
        }
        line++;
    }
    return 0;
}

int is_a_num(char c) {
    return (c >= '0' && c <= '9') || c == '.';
}

int get_priority(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '^':
            return 4;
        case '(':
            return 1;
        default:
            return 0;
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
            return (b != 0) ? a / b : NAN;
        case '^':
            return pow(a, b);
        default:
            return NAN;
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

        } else if (is_a_num(*infix) || (*infix == '-' && last_was_operator && (is_a_num(*(infix + 1)) || *(infix + 1) == '(')) || (*infix == '-' && last_was_operator)) {

            if (*infix == '-') {
                *postfix_ptr++ = '0';
                *postfix_ptr++ = ' ';
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
                if (current_operand == '(') {
                    has_open = 1;
                    break;
                }
                *postfix_ptr++ = current_operand;
                *postfix_ptr++ = ' ';
            }
            if (!has_open) {
                return ERROR_UNMATCHED_PARENTHESIS;
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
            return ERROR_UNKNOWN_SYMBOL;
        }
        infix++;
        position++;
    }
    while (!isEmptyChar(current)) {
        *postfix_ptr++ = popChar(&current);
        *postfix_ptr++ = ' ';
    }
    *postfix_ptr = '\0';
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
                return ERROR_NOT_ENOUGH_OPERANDS;
            }
            double a = pop(&current);
            double b = pop(&current);
            if (*input == '/' && a == 0) {
                return ERROR_DIVISION_BY_ZERO;
            }
            push(&current, apply_operator(b, a, *input));
            last_was_operator = 1;
        }
        input++;
    }
    if (current == NULL || current->next != NULL) {
        return ERROR_INVALID_POSTFIX;
    }
    *output = pop(&current);
    return 0;
}

void evaluate_expressions_from_file(const char *input_file, const char *output_file) {
    FILE *infile = fopen(input_file, "r");
    FILE *outfile = fopen(output_file, "w");
    if (!infile || !outfile) {
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), infile)) {

        line[strcspn(line, "\n")] = 0;

        char *postfix = malloc(strlen(line) * 2);
        if (!postfix) {
            fprintf(outfile, "Memory allocation failed for expression: %s\n", line);
            continue;
        }

        double result;
        int error_code = convert_from_infix_to_postfix(line, postfix);
        if (error_code != 0) {
            switch (error_code) {
                case ERROR_UNMATCHED_PARENTHESIS:
                    fprintf(outfile, "Error: Unmatched parentheses in expression: %s\n", line);
                    break;
                case ERROR_UNKNOWN_SYMBOL:
                    fprintf(outfile, "Error: Unknown symbol in expression: %s\n", line);
                    break;
                default:
                    fprintf(outfile, "Error processing expression: %s\n", line);
                    break;
            }
            free(postfix);
            continue;
        }

        error_code = calculate_RPN(postfix, &result);
        if (error_code != 0) {
            switch (error_code) {
                case ERROR_NOT_ENOUGH_OPERANDS:
                    fprintf(outfile, "Error: Not enough operands for operation in expression: %s\n", line);
                    break;
                case ERROR_DIVISION_BY_ZERO:
                    fprintf(outfile, "Error: Division by zero in expression: %s\n", line);
                    break;
                case ERROR_INVALID_POSTFIX:
                    fprintf(outfile, "Error: Invalid postfix expression: %s\n", line);
                    break;
                default:
                    fprintf(outfile, "Error processing expression: %s\n", line);
                    break;
            }
            free(postfix);
            continue;
        }

        fprintf(outfile, "Result: %s = %lf\n", line, result);
        free(postfix);
    }

    fclose(infile);
    fclose(outfile);
}

#endif