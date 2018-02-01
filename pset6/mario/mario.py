#!/usr/bin/env python3

from cs50 import get_int

# prompt user
while True:
    n = get_int("input a positive integer: ")
    if n >= 0 and n <= 23:
        break

# print pyramid
for row in range(1, n + 1):
    # print left pyramid
    print(" " * (n - row), end = "")
    print("#" * row, end = "")

    # print spaces
    print(" " * 2, end = "")

    # print right pyramid
    print("#" * row)