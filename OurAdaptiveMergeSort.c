/* ========================================================================= *
 * AdaptiveMergeSort
 * Implementation of the Adaptive Merge Sort algorithm.
 * ========================================================================= */
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "Sort.h"
#include "Array.h"


void merge(int tab[], int lo, int mid, int hi, int aux[]);
void mergeSortAux(int tab[], int lo, int hi, int aux[]);
void insertion(int *array,int start, size_t length);

void swap(int *var1, int *var2);
void swap_array(int *array,size_t start, size_t length);
int** create_index(size_t length);
void delete(int* lgs,int** indexs,size_t length);

int findRun(int *a, size_t start, size_t end, size_t minSize);
void fusion(int* array, int* lgs,int** indexs,int k,int* aux );
void adaptiveMergeSort(int* array,int* lgs,int** indexs,size_t length);




void merge(int tab[], int lo, int mid, int hi, int aux[]){

    int i = lo, j = mid;

    for (int k = lo; k <= hi; k++){
        if (i == mid){
            aux[k] = tab[j++];
        }else if (j == hi + 1){
            aux[k] = tab[i++];
        }else if (intCmp(tab[i], tab[j]) < 0){
            aux[k] = tab[i++];
        }else{
            aux[k] = tab[j++];
        }
    }
    for (int k = lo; k <= hi; k++){
        tab[k] = aux[k];
    }
}

void mergeSortAux(int tab[], int lo, int hi, int aux[]){

    int n = hi - lo + 1;
    if (n <= 1){
        return;
    }
    int mid = lo + (n + 1) / 2;
    mergeSortAux(tab, lo, mid - 1, aux);
    mergeSortAux(tab, mid, hi, aux);
    merge(tab, lo, mid, hi, aux);
}

void insertion(int *array,int start, size_t length){
    int j;
    int tmp;
    for (size_t i = start; i < length; i++){

        tmp = array[i];
        j = i;

        while (j > 0 && intCmp(array[j - 1], tmp) > 0){

            array[j] = array[j - 1];
            j--;
        }
        array[j] = tmp;
    }
}

void swap(int *var1, int *var2) {        
    int temporary_var;
    temporary_var = *var1;
    *var1 = *var2;
    *var2 = temporary_var;
}

void swap_array(int *array,size_t start, size_t length) {

    while (length > start) {

        swap(&array[start],&array[length-1]);
        start++;
        length--;
    }
}

int** create_index(size_t length){
    int **index = (int **)malloc(length * sizeof(int *));
    for (size_t j = 0; j < length; ++j){

        index[j] = (int *)malloc(2 * sizeof(int));        
    }
    return index;
}

void delete(int* tab_size,int** index,size_t length){

    for (size_t i = 0; i < length; ++i){
        free(index[i]);
    }
    free(index);
    free(tab_size);
}

int findRun(int* array, size_t start, size_t last, size_t minSize){

    size_t end_sort = start;
    size_t cond_out = 0;
    size_t out = 0;
    int flag_state = 0;
    int temp1;
    int temp2 = array[start];

    for (size_t i = start; i < last; ++i){

        temp1 = temp2;
        temp2 = array[i + 1];

        if (i == start && temp1 > temp2){
            flag_state = 1;
        }
        if (temp1 <= temp2 && flag_state == 0){
            end_sort++;
        }else if (temp1 > temp2 && flag_state == 1){
            end_sort++;
        }else{
            break;
        }
    }

    if ((start + minSize - 1) > last){
        cond_out = last;
    }else{
        cond_out = (start + minSize - 1);
    }
    if (flag_state == 1){
        swap_array(array,start,++end_sort);
    }
    out = end_sort;
    if (end_sort< cond_out){
        insertion(array,cond_out,end_sort);
        out = cond_out;
    }
    return out;
}

void fusion(int* array, int* lgs,int** index,int k,int* aux ){

    int temp_size_1 = lgs[k];
    int temp_size_2 = lgs[k-1];
    int temp_size_3 = lgs[k-2];

    int* temp_ind_1 = index[k];
    int* temp_ind_2 = index[k-1];
    int* temp_ind_3 = index[k-2];
    
    if (k >= 2){
        if (temp_size_3 <= temp_size_2 + temp_size_1){
            if (temp_size_1 >= temp_size_3){
                temp_ind_3[1] = temp_ind_2[1];
                temp_size_3 += temp_size_2;
                mergeSortAux(array, temp_ind_3[0], temp_ind_3[1], aux);

                temp_ind_2[0] = temp_ind_1[0];
                temp_ind_2[1] = temp_ind_1[1];
                temp_size_2 = temp_size_1;
                k--;
            }
            else if (temp_size_1 < temp_size_3){
                temp_ind_2[1] = temp_ind_1[1];
                temp_size_2 += temp_size_1;
                mergeSortAux(array, temp_ind_2[0], temp_ind_2[1], aux);
                k--;
            }
        }
        else if(lgs[k - 1] <= lgs[k]){
            temp_ind_2[1] = temp_ind_1[1];
            temp_size_2 += temp_size_1;
            mergeSortAux(array, temp_ind_2[0], temp_ind_2[1], aux);
            k--;
        }
    }
    else if (k == 1 && temp_size_2 <= temp_size_1){
        temp_ind_2[1] = temp_ind_1[1];
        temp_size_2 += temp_size_1;
        mergeSortAux(array, temp_ind_2[0], temp_ind_2[1], aux);
        k--;
    }

}

void adaptiveMergeSort(int* array,int* tab_size ,int** index,size_t length){

    size_t i = 0, j = 0, k = 0;
    int aux[length - 1];

    while(i < length)
    {
        j = i;
        index[k][0] = i;
        i = findRun(array, j, length - 1, 2);
        index[k][1] = i;
        tab_size[k] = (index[k][1] - index[k][0]) + 1;
        fusion(array,tab_size,index,k,aux);
        i++;
        k++;
    }

    k--;

    if (k >= 1)
    {
        for (int l = k; l > 0; l--)
        {
            index[l - 1][1] = index[l][1];
            tab_size[l - 1] += tab_size[l];
            mergeSortAux(array, index[l - 1][0], index[l - 1][1], aux);
        }
    }

}


void sort(int *array, size_t length){

    int** index = create_index(length);
    int* tab_size = malloc(length * sizeof(int));

    adaptiveMergeSort(array,tab_size,index,length);

    delete(tab_size,index,length);
}
