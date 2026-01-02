#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 100

void randomArray(int* array);
void bubbleSort(int* array);
void printArray(int* array);
void heapify(int* array, int size, int i);
void heapSort(int* array, int size);
void selectionSort(int* array);
void insertionSort(int* array);
int partition(int* array, int start, int end);
void quickSort(int* array, int start, int end);
void merge(int* array, int start, int middle, int end);
void mergeSort(int* array, int start, int end);

int main() {
    int choice = 0;
    int* array = (int*)calloc(MAX_LEN, sizeof(int));
    if (array == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }

    do {
        printf("\tMenu\n");
        printf("1. Bubble sort\n");
        printf("2. Insertion sort\n");
        printf("3. Selection sort\n");
        printf("4. Quick sort\n");
        printf("5. Heap sort\n");
        printf("6. Merge sort\n");
        printf("7. Exit program\n");
        printf("Choose an operation: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 7) {
            printf("Input error\n");
            exit(1);
        }

        switch (choice) {
            case 1:
                randomArray(array);
                bubbleSort(array);
                printf("Array after sorting:\n");
                printArray(array);
                break;
            case 2:
                randomArray(array);
                insertionSort(array);
                printf("Array after sorting:\n");
                printArray(array);
                break;
            case 3:
                randomArray(array);
                selectionSort(array);
                printf("Array after sorting:\n");
                printArray(array);
                break;
            case 4:
                randomArray(array);
                quickSort(array, 0, MAX_LEN - 1);
                printf("Array after sorting:\n");
                printArray(array);
                break;
            case 5:
                randomArray(array);
                heapSort(array, MAX_LEN);
                printf("Array after sorting:\n");
                printArray(array);
                break;
            case 6:
                randomArray(array);
                mergeSort(array, 0, MAX_LEN - 1);
                printf("Array after sorting:\n");
                printArray(array);
                break;
            case 7:
                printf("Exiting the program...");
                free(array);
                exit(1);
        }
    } while (choice != 7);

    return 0;
}

void randomArray(int* array) {
    int min = 1;
    printf("Array before sorting:\n");
    for (int i = 0; i < MAX_LEN; i++) {
        array[i] = rand() % (MAX_LEN - min - 1) + min;
    }
    printArray(array);
}

void bubbleSort(int* array) {
    for (int i = 0; i < MAX_LEN - 1; i++) {
        for (int j = 0; j < MAX_LEN - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printArray(int* array) {
    int index = 0;
    for (int i = 0; i < MAX_LEN / 20; i++) {
        for (int j = 0; j < MAX_LEN / 5; j++) {
            printf("%d ", array[index++]);
        }
        printf("\n");
    }
    printf("\n");
}

void heapify(int* array, int size, int i) {
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && array[left] > array[max]) {
        max = left;
    }
    if (right < size && array[right] > array[max]) {
        max = right;
    }

    if (i != max) {
        int tmp = array[max];
        array[max] = array[i];
        array[i] = tmp;
        heapify(array, size, max);
    }
}

void heapSort(int* array, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        heapify(array, i, 0);
    }
}

void selectionSort(int* array) {
    for (int i = 0; i < MAX_LEN - 1; i++) {
        int min_idx = i;

        for (int j = i + 1; j < MAX_LEN; j++) {
            if (array[j] < array[min_idx]) {
                min_idx = j;
            }
        }

        int temp = array[i];
        array[i] = array[min_idx];
        array[min_idx] = temp;
    }
}

void insertionSort(int* array) {
    for (int i = 1; i < MAX_LEN; i++) {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

int partition(int* array, int start, int end) {
    int x = array[end];
    int tmp;
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (array[j] <= x) {
            i++;
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    }

    tmp = array[i + 1];
    array[i + 1] = array[end];
    array[end] = tmp;

    return i + 1; 
}

void quickSort(int* array, int start, int end) {
    if (start < end) { 
        int plt_ind = partition(array, start, end);
        quickSort(array, start, plt_ind - 1);
        quickSort(array, plt_ind + 1, end);
    }
}

void merge(int* array, int start, int middle, int end) {
    int n1 = middle - start + 1;
    int n2 = end - middle;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[start + i];
    for (int j = 0; j < n2; j++)
        M[j] = array[middle + 1 + j];

    int i, j, k;
    i = 0;      
    j = 0;      
    k = start;  
    
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int* array, int start, int end) {
    if (start < end) {
        int middle = start + (end - start) / 2;
        mergeSort(array, start, middle);
        mergeSort(array, middle + 1, end);
        merge(array, start, middle, end);
    }
}
