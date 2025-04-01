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


#define ERROR_NONE 0
#define ERROR_DIV_BY_ZERO 1
#define ERROR_NEGATIVE_EXP_ZERO 2
#define ERROR_OVERFLOW 3
#define ERROR_UNKNOWN_OPERATOR 4


double apply_operator(double a, double b, char operator, int* error_code) {
    *error_code = ERROR_NONE;

    switch (operator) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            if (fabs(a) > DBL_MAX / fabs(b)) {
                *error_code = ERROR_OVERFLOW;
                return NAN;
            }
        return a * b;
        case '/':
            if (b == 0) {
                *error_code = ERROR_DIV_BY_ZERO;
                return NAN;
            }
        return a / b;
        case '^':
            if (a == 0 && b < 0) {
                *error_code = ERROR_NEGATIVE_EXP_ZERO;
                return NAN;
            }
        if (b > 30) {
            *error_code = ERROR_OVERFLOW;
            return NAN;
        }
        double result = pow(a, b);
        if (!isfinite(result)) {
            *error_code = ERROR_OVERFLOW;
            return NAN;
        }
        return result;
        default:
            *error_code = ERROR_UNKNOWN_OPERATOR;
        return NAN;
    }
}

int convert_from_infix_to_postfix(char *infix, char *postfix, int prew_pos[256], FILE *output) {
    struct Char_Node *current = NULL;
    char *postfix_ptr = postfix;
    int position = 0;
    int last_was_operator = 1;
    int postfix_index = 0;

    while (*infix != '\0') {
        if (*infix == ' ') {
            infix++;
            continue;
        }

        if (is_a_num(*infix) || (*infix == '-' && last_was_operator && (is_a_num(infix[1]) || infix[1] == '('))) {
            int operand_start = position;
            do {
                *postfix_ptr++ = *infix++;
                position++;
            } while (is_a_num(*infix) || *infix == '.');

            *postfix_ptr++ = ' ';
            prew_pos[postfix_index++] = operand_start;
            last_was_operator = 0;
            continue;
        }

        if (*infix == '(') {
            pushChar(&current, *infix);
            prew_pos[postfix_index++] = position;
            last_was_operator = 1;
            infix++;
            position++;
            continue;
        }

        if (*infix == ')') {
            int has_open = 0;
            while (!isEmptyChar(current)) {
                char op = popChar(&current);
                if (op == '(') {
                    has_open = 1;
                    break;
                }
                *postfix_ptr++ = op;
                *postfix_ptr++ = ' ';
                prew_pos[postfix_index++] = position - 1;
            }
            if (!has_open) {
                fprintf(output, "Error in position %d: unmatched ')'\n", position);
                return 1;
            }
            infix++;
            position++;
            last_was_operator = 0;
            continue;
        }

        if (char_in_line(*infix, "+-*/^")) {
            while (!isEmptyChar(current) && get_priority(peekChar(current)) >= get_priority(*infix)) {
                char op = popChar(&current);
                *postfix_ptr++ = op;
                *postfix_ptr++ = ' ';
                prew_pos[postfix_index++] = position - 1;
            }
            pushChar(&current, *infix);
            prew_pos[postfix_index++] = position;
            last_was_operator = 1;
            infix++;
            position++;
            continue;
        }

        fprintf(output, "Error in position %d: unknown symbol '%c'\n", position, *infix);
        return 1;
    }


    while (!isEmptyChar(current)) {
        char op = popChar(&current);
        *postfix_ptr++ = op;
        *postfix_ptr++ = ' ';
        prew_pos[postfix_index++] = position - 1;
    }

    *postfix_ptr = '\0';

    printf("%s\n", postfix);

    for (int i = 0; i < postfix_index; i++) {
        printf("Postfix symbol: %c at position %d in infix\n", postfix[i], prew_pos[i]);
    }

    return 0;
}

int calculate_RPN(char *input, char *output, int prew_pos[100]) {
    struct Node* current = NULL;
    int is_num = 0, iter = 0, position = 0;
    char buffer[30] = "";
    int last_was_operator = 1;
    int postfix_index = 0;
    char *original_input = input;

    while (*input != '\0') {

        int is_unary_minus = (*input == '-' && (position == 0 || (input > original_input && *(input - 1) == ' ')));

        if (is_a_num(*input) || *input == '.' || is_unary_minus) {
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
                postfix_index++;
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
                postfix_index++;
            }


            if (current == NULL || current->next == NULL) {
                int error_pos = prew_pos[postfix_index];
                sprintf(output, "Ошибка в позиции %d: недостаточно операндов для оператора %c", error_pos, *input);
                return 1;
            }

            double a = pop(&current);
            double b = pop(&current);
            int error_code;
            double result = apply_operator(b, a, *input, &error_code);

            if (error_code != ERROR_NONE) {
                const char *error_message;
                switch (error_code) {
                    case ERROR_OVERFLOW: error_message = "переполнение"; break;
                    case ERROR_DIV_BY_ZERO: error_message = "деление на ноль"; break;
                    case ERROR_NEGATIVE_EXP_ZERO: error_message = "нулевая база с отрицательной степенью"; break;
                    default: error_message = "неизвестная ошибка"; break;
                }
                sprintf(output, "Ошибка в позиции %d: %s", prew_pos[postfix_index], error_message);
                return 1;
            }

            push(&current, result);
            postfix_index++;
            last_was_operator = 1;
        }
        input++;
        position++;
    }


    if (is_num) {
        buffer[iter] = '\0';
        double temp;
        sscanf(buffer, "%lf", &temp);
        push(&current, temp);
        postfix_index++;
    }


    if (current == NULL || current->next != NULL) {
        int error_pos = postfix_index > 0 ? prew_pos[postfix_index - 1] : 0;
        sprintf(output, "Ошибка в позиции %d: некорректное выражение", error_pos);
        return 1;
    }

    sprintf(output, "%lf", pop(&current));
    return 0;
}





void process_evaluation(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        printf("Error opening input file\n");
        return;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        printf("Error opening output file\n");
        fclose(input_file);
        return;
    }

    char expression[256];
    int prew_pos[256];
    while (fgets(expression, sizeof(expression), input_file)) {
        size_t len = strlen(expression);
        if (len > 0 && expression[len - 1] == '\n') {
            expression[len - 1] = '\0';
        }

        char *postfix = malloc(strlen(expression) * 2);
        if (!postfix) {
            printf("Memory allocation failed\n");
            continue;
        }

        char output[256];

        if (convert_from_infix_to_postfix(expression, postfix, prew_pos, output_file) != 0 || calculate_RPN(postfix, output, prew_pos) != 0) {
            fprintf(output_file, "%s\n", output);
            free(postfix);
            continue;
        }

        double result;
        sscanf(output, "%lf", &result);
        fprintf(output_file, "%.6f\n", result);

        free(postfix);
    }

    fclose(input_file);
    fclose(output_file);
}


#endif
