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

            printf("������������ ������ ����� 3\n");
            printf("������ ����� (������� ����� ����� �������):\n");
            printf("\n1 - ����� �������� ������� �����, �� �������� �� ������\n");
            printf("2 - ����������� ���� ������\n");
            printf("3 - ��������� ��������� � ��������� �����\n\n");

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
                printf("\n\n��������� ��������� � ��������� ����� -output.txt-\n");
                break;
            default:
                loop = 0;
                break;
        }


    }

    system("pause");
}