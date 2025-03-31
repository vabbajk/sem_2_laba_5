#ifndef HEADER_H
#define HEADER_H


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <limits.h>
#include <math.h>

int check_int_1(const char *input, int min, int max) {
    if (input == NULL || *input == '\0') {
        return 0;
    }

    const char *ptr = input;
    int is_negative = 0;

    if (*ptr == '-') {
        if (min >= 0) {
            return 0;
        }
        is_negative = 1;
        ptr++;
    }

    if (*ptr == '\0') {
        return 0;
    }

    long long int result = 0;
    while (*ptr != '\0') {
        if (*ptr < '0' || *ptr > '9') {
            return 0;
        }
        int digit = *ptr - '0';

        result = result * 10 + digit;
        ptr++;
    }

    if (is_negative) {
        result = -result;
    }

    if (result < min || result > max) {
        return 0;
    }

    return 1;
}

int new_input_metod(int min, int max) {
    int size = 0;
    int res = 0;
    int has_num = 0;

    char* line = (char*)malloc(1);
    if (line == NULL) {
        return -2;
    }
    line[0] = '\0';

    while (1) {
        char key = _getch();

        if (key == 27) {
            free(line);
            return INT_MIN;
        }

        if (key == ' ') {
            if (size > 0 && line[size - 1] != ' ' && line[size - 1] != '-') {
                char* temp = realloc(line, size + 2);
                if (temp == NULL) {
                    free(line);
                    return -2;
                }
                line = temp;
                line[size] = ' ';
                line[size + 1] = '\0';
                printf(" ");
                size++;
                has_num = 0;
            }
        }
        else if (key == '-') {
            if (size == 0 || line[size - 1] == ' ') {
                char* temp = realloc(line, size + 2);
                if (temp == NULL) {
                    free(line);
                    return -2;
                }
                line = temp;
                line[size] = '-';
                line[size + 1] = '\0';
                printf("-");
                size++;
                has_num = 1;
            }
        }

        else if (key >= '0' && key <= '9') {
            if ((size == 1 && line[0] == '0') ||
                (size > 1 && line[size - 1] == '0' && (line[size - 2] == ' ' || line[size - 2] == '-'))) {
                continue;
            }

            char* temp = realloc(line, size + 2);
            if (temp == NULL) {
                free(line);
                return -2;
            }
            line = temp;
            line[size] = key;
            line[size + 1] = '\0';
            printf("%c", key);
            size++;
            has_num = 1;
        }

        else if (key == '\b') {
            if (size > 0) {
                printf("\b \b");
                size--;
                char* temp = realloc(line, size + 1);
                if (temp == NULL) {
                    free(line);
                    return -2;
                }
                line = temp;
                line[size] = '\0';
                if (size == 0 || line[size - 1] == ' ' || line[size - 1] == '-') {
                    has_num = 0;
                }
            }
        }

        else if (key == '\r' || key == '\n') {
            if (size > 0 && line[size - 1] != '-' && check_int_1(line, min, max)) {
                break;
            }
        }
    }

    printf("\n");

    sscanf(line, "%lld", &res);
    free(line);
    return res;
}

char choce_task_n_to_m(char n, char m) {
    char c = 'l';
    while (c < n || c > m) {
        c = _getch();
    }
    return c;
}

void print_task() {
    puts("5-я лабораторная работа, тема - =СТЕК=\n");
    puts("1 - ввести два стека целых чисел, вывести элементы первого стека, не входящие во второй\n");
    puts("2 - Создать два стека для целых чисел. Первый стек – организовать ввод по возрастанию,"
            "второй стек – организовать ввод по возрастанию. Без сортировок и переворачивания"
            "исходных стеков сформировать третий стек упорядоченный по возрастанию\n");
    puts("3 - В текстовом файле записаны строки – арифметические выражения. Числа – вещественные,"
            "знаки действий - -, +, *, / и скобки (). Используя работу со стеками найти значение каждого выражения"
            "и записать в файл результатов. Если в исходном файле в строке есть ошибка – найти ее предполагаемую"
            "позицию (позицию первой ошибки) и в выходной файл записать сообщение «Ошибка в позиции N»\n");
    puts("4 - Выход\n");

    puts("Выберите задание : ");
}

#endif