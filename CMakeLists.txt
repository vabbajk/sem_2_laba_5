cmake_minimum_required(VERSION 3.10)
project(sem_2_lab_5 C)

set(CMAKE_C_STANDARD 11)

# Добавляем исполняемый файл (только main.c, потому что других .c файлов нет)
add_executable(sem_2_lab_5 main.c
        Union_stack.h
        Text_file_processing.h)
