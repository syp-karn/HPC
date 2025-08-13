// All code optimizations are done with O1 compiler omptimization

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000  // 1 million elements
#define SWAP(a, b) do { int tmp = (a); (a) = (b); (b) = tmp; } while(0) // Swap macro decreased exec time from 0.26s to 0.14s

// Swap two elements
// void swap(int *a, int *b) {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

int median_of_three(int a, int b, int c) {   // using median of three for pivot selection didn't provide much speedup; same exec times of around 0.25s
    if ((a > b) != (a > c)) return a;
    else if ((b > a) != (b > c)) return b;
    else return c;
}

// Partition function for QuickSort
int partition(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;

    // find median value
    int median_val = median_of_three(arr[low], arr[mid], arr[high]);

    // move median to the end as pivot
    if (median_val == arr[low]) {
        SWAP(arr[low], arr[high]);
    } else if (median_val == arr[mid]) {
        SWAP(arr[mid], arr[high]);
    }
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            SWAP(arr[i], arr[j]);
        }
    }
    SWAP(arr[i + 1], arr[high]);
    return (i + 1);
}

// QuickSort recursive function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int *arr = (int*)malloc(SIZE * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));

    // Fill array with random integers
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand();
    }

    // Measure execution time
    clock_t start, end;
    start = clock();

    quickSort(arr, 0, SIZE - 1);

    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("QuickSort of %d elements took %.2f seconds.\n", SIZE, time_taken);

    free(arr);
    return 0;
}