#include <stdio.h>
#include "Header.h"
#include "In_second_stack.h"
#include "Union_stack.h"
#include "Text_file_processing.h"

int main(void) {
    int loop = 1;

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    while (loop) {
        print_task();

        char c = choce_task_n_to_m('1', '4');

        switch (c) {
            case '1':

                in_second_stack();
                break;

            case '2':

                union_stack();
                break;

            case '3':

                processFile("input.txt", "output.txt");
                printf("\n\nРезультат находится в файле =output.txt=\n");
                break;

            default:

                loop = 0;
                break;
        }

        system("pause");
        system("cls");
    }

}