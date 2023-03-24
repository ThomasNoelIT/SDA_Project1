/* ========================================================================= *
 * QuickSort
 * Implementation of the QuickSort algorithm.
 * ========================================================================= */

#include "Sort.h"
#include "Array.h"
#include "stdio.h"
#include <stdlib.h>

void swap(int *var1, int *var2);
int partitioning(int *array, int bottom, int top);
void quicksort(int *array, int bottom, int top);
void sort(int *array, size_t length);

//fonction de base : swap les pointeurs des éléments
void swap(int *var1, int *var2) {        
    int temporary_var;
    temporary_var = *var1;
    *var1 = *var2;
    *var2 = temporary_var;
}


int partitioning(int *array, int bottom, int top) {
    int pivot = array[top];
    int i = (bottom - 1);

    for (int j = bottom; j <= top - 1; j++) {
        if (intCmp(array[j], pivot) < 0) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[top]);
    return (i + 1);
}

void quicksort(int *array, int bottom, int top) {
    if (bottom < top) {
        int pi = partitioning(array, bottom, top);

        quicksort(array, bottom, pi - 1);
        quicksort(array, pi + 1, top);
    }
}

void sort(int *array, size_t length){
    void resetCounter();
    int lth = (int)length-1;
    quicksort(array, 0, lth);    
    return;
}
