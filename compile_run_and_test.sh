#!/bin/bash

# Compile task main file and unit testing file.
###############################################

clang++ -std=c++14 -pedantic-errors -Wall -Wextra -g -o unit_test.out \
average_buffer_unit_test.cpp

valgrind --leak-check=yes --track-origins=yes ./unit_test.out