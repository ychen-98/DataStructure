#include <iostream>
using namespace std;

const int MAX_N = 1000;  // Maximum allowed size for the array

// void: This indicates that the function doesn't return any value.

// The function std::swap() is a built-in function in the C++ Standard Template Library (STL)
// which swaps the value of two variables.

// Selection Sort Algorithm
void SelectionSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[min_idx])
                min_idx = j;
        }
        swap(array[min_idx], array[i]);
    }
}

int main() {
    int N;
    int data[MAX_N];  // Array of size MAX_N

    // Getting user input for N
    cout << "Enter the number of elements (max " << MAX_N << "): ";
    cin >> N;

    if (N > MAX_N || N <= 0) {
        cout << "Invalid size!" << endl;
        return 1;  // Exit the program with an error code
    }

    // Getting user input for the elements
    cout << "Enter " << N << " integers:" << endl;
    for (int i = 0; i < N; i++) {
        cin >> data[i];
    }

    // Sorting the array
    SelectionSort(data, N);

    // Printing the sorted array
    cout << "Sorted array in Ascending Order:" << endl;
    for (int i = 0; i < N; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;  // Successful execution
}
