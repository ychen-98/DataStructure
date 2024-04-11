Selection Sort Program README
=============================

Description:
------------
This program is written in C++ and performs the Selection Sort algorithm on an array of integers. The user provides the length of the array and its elements. The program then sorts the array in ascending order and displays the result.

Source File:
------------
- main.cpp: Contains the main function and the SelectionSort routine.

Compilation and Usage:
----------------------
A makefile is provided with the program to ease the compilation and running processes.

- To compile the program:
  $ make

- To run the program:
  $ make run

  You will be prompted to:
  1. Enter the number of elements (maximum of 1000).
  2. Enter the integers. These can be provided each on a separate line or in one line separated by spaces.

  The program will then display the sorted array in ascending order.

- To clean the build (remove object files and the compiled executable):
  $ make clean

Input Format:
-------------
1. First, input the number of elements, N (where 1 <= N <= 1000).
2. Then, enter N integers. They can be provided:
   - Each on a separate line.
   - Or, in one line separated by spaces.

Example:
--------
$ make run
> Enter the number of elements (max 1000): 5
> Enter 5 integers:
> 4 3 1 5 2
> Sorted array in Ascending Order:
> 1 2 3 4 5

Notes:
------
- If you input a value of N outside the range (like more than 1000 or less than 1), the program will display an "Invalid size!" message and terminate.
- The SelectionSort() function is a routine called within the main function to perform the sorting.

Author:
-------
Yao Chen 
