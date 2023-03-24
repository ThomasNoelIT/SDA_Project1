/* ========================================================================= *
 * HeapSort
 * Implementation of the HeapSort algorithm.
 * ========================================================================= */

#include "Sort.h"
#include "Array.h"
#include "stdio.h"
#include <stdlib.h>

void swap(int *var1, int *var2);
void maintain_ownership(int *array, size_t length, int i);
void build_max_tree(int *array, size_t length);
void sort(int *array, size_t length);

//fonction de base : swap les pointeurs des éléments
void swap(int *var1, int *var2) {        
    int temporary_var;
    temporary_var = *var1;
    *var1 = *var2;
    *var2 = temporary_var;
}

//récursif
void maintain_ownership(int *array, size_t length, int i){
    int node = i;
    int left = 2*i+1;
    int right = 2*i+2;

    while (left < (int)length &&  intCmp(array[node], array[left]) < 0){
        node = left;
    }

    while (right < (int)length && intCmp(array[node], array[right]) < 0 ){
        node = right;
    }

    if (node != i) {
        swap(&array[i], &array[node]);
        maintain_ownership(array, length, node);
    }
}

void build_max_tree(int *array, size_t length){
    for(int i = length/2-1; i >= 0; i--){
        maintain_ownership(array, length, i);
    }
}

void sort(int *array, size_t length)
{
    void resetCounter();
    build_max_tree(array, length);

    for(int i = length-1; i > 0; i--){
        swap(&array[0], &array[i]);
        maintain_ownership(array, i, 0);
    }
}