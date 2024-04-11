B-tree Implementation and Search in C++

Yao Chen 
Oct 18, 2023 

## Overview
This program demonstrates the implementation of a B-tree in C++. Specifically, it builds a 5-way B-tree using randomly generated integers.


## Compilation: 
	make

## Execution: 
	make run 

## Cleaning: 
	make clean 

## Input: 
N: The number of random integers to be generated and inserted into the B-tree. These integers will range between 0 and 3*N.


## Output: 
The B-tree Content: Displays the keys of the B-tree in ascending order.
Keys in Specified Range: Lists the keys present in the range [N, 2*N].


## Example: 
make
make run
[Input] 
Generate a sequence of N random integers (keys), in the range [0,...,3*N]
Enter the value of N (N >= 400): 500
[Output] 
The B-tree is: 5 10 20 25 30 35 ... (and so on, in ascending order)
Keys in the range [500, 1000]: 502 509 513 525 ... (and so on, keys between 500 and 1000)


## Code Structure
- **TreeNode Class**: Represents a node in the B-tree. Each node can contain keys and child pointers. It provides functions like `insertNonFull` and `splitChild` to aid in the insertion process.
  
- **BTree Class**: Represents the B-tree structure. It offers core functionalities like insertion (`insert` function) and search (`search` function). The tree is initialized with a degree `t`. In this program, `t=5`, which results in a 5-way B-tree.

- **rangeSearch Function**: Given a B-tree node and a key range, this function returns all the keys that fall within the specified range.


## How the Program Works
1. The user is prompted to provide a value for `N`.
2. The program generates `N` random integers in the range [0, 3*N].
3. These integers are inserted into a 5-way B-tree in the sequence they are generated.
4. The program outputs the B-tree's keys and displays the keys that are in the range [N, 2*N].

Note: The B-tree traversal in the program is in-order, meaning it will display the keys in ascending order.