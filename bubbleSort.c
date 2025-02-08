// Merkins, William
// Chpt3 PA

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 25  // Define the size of the array

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to implement Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) { // Outer loop for passes
        for (int j = 0; j < n - i - 1; j++) { // Inner loop for comparisons
            if (arr[j] > arr[j + 1]) { // Swap if elements are out of order
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[SIZE]; // Declare array
    srand(time(0)); // Seed random number generator

    // Fill array with random numbers between 1 and 1000
    for (int i = 0; i < SIZE; i++) {
        arr[i] = (rand() % 1000) + 1;
    }

    // Print unsorted array
    printf("Unsorted array:\n");
    printArray(arr, SIZE);

    // Sort the array using Bubble Sort
    bubbleSort(arr, SIZE);

    // Print sorted array
    printf("Sorted array:\n");
    printArray(arr, SIZE);

    return 0;
}
