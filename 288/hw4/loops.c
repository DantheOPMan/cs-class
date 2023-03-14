#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int arr[], int n) {
    int i, j, min_index, temp;
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}


int getMax(int arr[], int n) {
    int max = arr[0];
    int i;
    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void radixSort(int arr[], int n) {
    int i, exp = 1;
    int bucket[10] = {0};
    int *output = calloc(n, sizeof(int));

    int max = getMax(arr, n);

    while (max / exp > 0) {
        for (i = 0; i < 10; i++) {
            bucket[i] = 0;
        }

        for (i = 0; i < n; i++) {
            bucket[(arr[i] / exp) % 10]++;
        }

        for (i = 1; i < 10; i++) {
            bucket[i] += bucket[i - 1];
        }

        for (i = n - 1; i >= 0; i--) {
            output[bucket[(arr[i] / exp) % 10] - 1] = arr[i];
            bucket[(arr[i] / exp) % 10]--;
        }

        for (i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        exp *= 10;
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = calloc(n1, sizeof(int)), *R = calloc(n2, sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }


}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void genArray(int arr[], int size){
    int i;
    srand(time(NULL));
    for (i = 0; i < size; i++) {
        arr[i] = rand() % size;
    }
}

void setArray(int input[], int arr[], int arrSize){
    int i;
    for (i = 0; i < arrSize; i++) {
        input[i] = arr[i];
    }
}

void outputArray(int arr[], int arrSize){
    int i;
    for (i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arrSize = 10;
    int *arr;
    int *inputArray;
    clock_t startTime, endTime;
    double outputTime;
    
    for(arrSize = 10; arrSize <= 1000000000; arrSize *= 10){
        arr = calloc(arrSize,sizeof(int));
        inputArray = calloc(arrSize,sizeof(int));
        genArray(arr, arrSize);

        /*Selection Sort*/
        if(arrSize <=1000000){
            setArray(inputArray, arr, arrSize);
            startTime = clock(); 
            selection_sort(inputArray, arrSize);
            endTime = clock();  
            outputTime = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
            printf("Time taken Selection Sort with Arr size %d: %f seconds\n", arrSize,outputTime);
        }
        
        
        /*Merge Sort*/
        if(arrSize <=100000000){
            setArray(inputArray, arr, arrSize);
            startTime = clock(); 
            mergeSort(inputArray, 0, arrSize);
            endTime = clock();  
            outputTime = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
            printf("Time taken Merge Sort with Arr size %d: %f seconds\n", arrSize,outputTime);
        }
        

        /*Radix Sort*/
        setArray(inputArray, arr, arrSize);
        startTime = clock(); 
        radixSort(inputArray, arrSize);
        endTime = clock();  
        outputTime = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
        printf("Time taken Radix Sort with Arr size %d: %f seconds\n", arrSize,outputTime);
        
        /*Free*/
        free(arr);
        free(inputArray);
    }
    return 0;
}
