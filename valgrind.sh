#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all -s --log-file="valgrind_output.txt" ./rename.c