#include <stdio.h>
#include "Header.h"
#include "Not_int_second_stack.h"
#include "Union_stack.h"
#include "Text_file_processing.h"

int main(void) {

    int loop = 1;

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    while (loop) {

            printf("Лабораторная работа номер 3\n");
            printf("Список задач (нажмите цифру чтобы выбрать):\n");
            printf("\n1 - Вывод значений первого стэка, не сходящих во второй\n");
            printf("2 - Объеденение двух стэков\n");
            printf("3 - Обработка уравнений в текстовом файле\n\n");

            char c = choce_task_n_to_m('1', '3');

        switch (c) {
            case '1':
                not_int_second_stack();
                break;
            case '2':
                union_stack();
                break;
            case '3':
                processFile("input.txt", "output.txt");
                printf("\n\nРезультат находится в текстовом файле -output.txt-\n");
                break;
            default:
                loop = 0;
                break;
        }


    }

    system("pause");
}