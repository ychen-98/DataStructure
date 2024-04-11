Binary Search Tree (BST) 

Yao Chen 
Sep 27, 2023 


Introduction: 
This project is designed to take an unordered list of integers and build a balanced binary search tree (BST). Additionally, it can find and display the k-th smallest element in the BST.


Compilation: 
	make

Execution: 
	make run 

Cleaning: 
	make clean 

Input: 
A predefined vector of integers. 
User-input for the value of k to find the k-th smallest element in the BST.

Output: 
A printed structured format of the BST.
The k-th smallest element in the BST or an error message if k is invalid.


Example: 
If you want to find the 10th smallest element, enter 10 when prompted.

make
make run
Enter the value of k (between 1 and 15) : 10


Explanation of the "Sorted Array to BST" Method:

1. Sort the Input Array: 
Before constructing a balanced BST, sort the input array in ascending order. Sorting ensures that when we pick the middle element, smaller elements are to its left and larger elements are to its right, fitting the property of a BST.

2. Choosing the Middle Element: 
For a sorted array, the middle element becomes the root of the BST. This decision ensures a balanced split of elements for the left and right subtrees, making the tree as balanced as possible.

3. Recursive Construction:
Once the middle element is picked as the root, the elements on the left half of the middle element become part of the left subtree, and the elements on the right half become part of the right subtree.
Recursively, the process is repeated for the left and right halves by picking their middle elements.