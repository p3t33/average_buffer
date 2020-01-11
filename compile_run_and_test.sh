#!/bin/bash

# Compile task main file and unit testing file.
###############################################

clang++ -std=c++14 -pedantic-errors -Wall -Wextra -g \
average_buffer_unit_test.cpp \
-o average_buffer_unit_test.out 


valgrind --leak-check=yes --track-origins=yes ./unit_test.out