/* ========================================================================= *
 * AdaptiveMergeSort
 * Implementation of the Adaptive Merge Sort algorithm.
 * ========================================================================= */

#include "Sort.h"
#include "Array.h"
#include "stdio.h"
//#include "pthread.h"
#include <stdlib.h>
#include <time.h> 



typedef struct StackElement {
    size_t start;
    size_t end;
} StackElement;

typedef struct Stack {
    int max_size;
    StackElement* data; // Pointeur vers le début du tableau de données
    int top; 
} Stack;

// Initialise une pile vide
static Stack* createStack(size_t size) {

    Stack* stack = (Stack*)malloc(sizeof(Stack));

    stack->max_size = size;
    stack->data = (StackElement*)malloc(sizeof(StackElement) * size);
    stack->top = -1;
    return stack;
}

// Vérifie si la pile est vide
static int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Vérifie si la pile est pleine
static int isFull(Stack* stack) {
    return stack->top == stack->max_size-1;
}

// Ajoute un élément au sommet de la pile
static void push(Stack* stack, size_t start, size_t end) {
    if (isFull(stack)) {
        printf("Erreur : pile pleine.\n");
        return;
    }
    //printf("end in push = %ld\n",end);
    stack->data[stack->top].start = start;
    stack->data[stack->top].end = end;
    stack->top++;
}

// Retire et retourne l'élément au sommet de la pile
static StackElement pop(Stack* stack) {
    StackElement data;
    if (isEmpty(stack)) {
        printf("Erreur : pile vide.\n");
        data.start = -1;
        data.end = -1;
        return data;
    }
    data = stack->data[--stack->top];
    return data;
}

/*
// Retourne l'élément au sommet de la pile sans le retirer
static StackElement peek(Stack* stack) {
    StackElement data;
    if (isEmpty(stack)) {
        printf("Erreur : pile vide.\n");
        data.start = -1;
        data.end = -1;
        return data;
    }
    data = stack->data[stack->top - 1];
    return data;
}*/

/*static void print_stack(struct Stack* s) {
    int i;
    if (isEmpty(s)) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements:\n");
        for (i = s->top; i >= 0; i--) {
            printf("start = %ld, end = %ld\n", s->data[i].start,s->data[i].end);
        }
    }
}*/


// Libère la mémoire allouée pour la pile
static void deleteStack(Stack* stack) {
    if(stack == NULL){
        return;
    }
    //printf("je free les datas\n");
    free(stack->data);
    //printf("je free le stack\n");
    free(stack);
    
}


int findRun(int *array, size_t start,size_t last, size_t minSize);


static void swap(int *var1, int *var2) {        
    int temporary_var;
    temporary_var = *var1;
    *var1 = *var2;
    *var2 = temporary_var;
}

static void insertion(int *array,int start, size_t length){
    int j;
    int tmp;
    // Invariant: array[0..i] is sorted
    for (size_t i = start; i < length; i++)
    {
        tmp = array[i];
        j = i;
        // Place tmp at the right position
        while (j > 0 && intCmp(array[j - 1], tmp) > 0)
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = tmp;
    }
}

static void merge(int* array, int lo, int mid, int hi, int aux[])
{
    int i = lo, j = mid;

    for (int k = lo; k <= hi; k++){
        if (i == mid)
            aux[k] = array[j++];
        else if (j == hi + 1)
            aux[k] = array[i++];
        else if (intCmp(array[i],  array[j]) < 0)
            aux[k] = array[i++];
        else
            aux[k] = array[j++];
    }
    for (int k = lo; k <= hi; k++){
        array[k] = aux[k];
    }
}

static void swap_array(int *array,size_t start, size_t length) {
    size_t end = length;
    //size_t end = length-1;

    while (end > start) {
        swap(&array[start],&array[end-1]);
        start++;
        end--;
    }
}


//du plus petit au plus grand
int findRun(int *array, size_t start, size_t last, size_t minSize){
    
    size_t end = start;
    //size_t length = last-start;
    size_t length = last;
    size_t i;

    int temp1 = array[start];
    int temp2 = array[start+1];

    //printf("length = %ld\n",length);

    int flag_state = 0;
    for(i = start; i < length; i++){
        //printf("start = %ld\n",start);
        //printf("end = %ld\n",end);
        
        if(i+1 < last){
            //printf("state = %d\n",state);
            
            if(i == start && temp1> temp2){
                flag_state = 1;
            }

            if(flag_state == 0){
                if(temp1< temp2){
                    end++;
                }

                if(temp1> temp2){
                    
                    //if(i < minSize){
                        //insertion(array,start,minSize);
                        //end = start+minSize;
                    //}
                    break;
                }
            }else if(flag_state == 1){
                if(temp1> temp2){
                    end++;
                }
                if(temp1< temp2){
                    //printf("je retourne le tableau\n");
                    
                    //swap_array(array,start,i);
                    //if(intCmp(i, minSize) < 0){
                      //  insertion(array,start,minSize);
                        //end = start+minSize;
                    //}
                    
                    break;
                }

            }
        }
        temp1 = temp2;
        temp2 = array[i+2];
    }
/*
    size_t index_fin_tri = start;
    size_t cond_out = 0, out = 0;
    int flag_inv = 0;
    for (size_t i = start; i < last; ++i)
    {
        if (i == start && array[i] > array[i + 1])
            flag_inv = 1;

        if (array[i] <= array[i + 1] && flag_inv == 0)
            index_fin_tri++;
        else if (array[i] > array[i + 1] && flag_inv == 1)
            index_fin_tri++;
        else
            break;
    }
    if ((start + minSize - 1) > last)
        cond_out = last;
    else
        cond_out = (start + minSize - 1);
    if (flag_inv == 1)
    {
        int tmp = 0;
        size_t k = start, l = index_fin_tri;

        while(k < l)
        {
            tmp = array[k];
            array[k] = array[l];
            array[l] = tmp;
            k++;
            l--;
        }
    }*/

    
    if(flag_state == 1){
        swap_array(array,start,i);
    }

    if(start+minSize < length){
    //if(end+1-start < minSize){
        if(i < minSize){
            //printf("je rentre car i < min size: i = %ld et minsize = %ld\n",i,minSize);
            insertion(array,start,minSize);
            end = start+minSize;
        } 
    }else{
        insertion(array,start,length);
        end = length;
    }
    return end;
    
/*
       // updating the value returned by findrun
    out = index_fin_tri;

    // use of Insertiion sort if the already sorted part of the subarray is smaller than start + minSize
    if (index_fin_tri < cond_out)
    {
        size_t j;
        int tmp;
        // invariant : array[0..i] is sorted
        for (size_t i = index_fin_tri; i <= cond_out; i++)
        {
            tmp = array[i];
            j = i;
            // place tmp at the right position
            while (j > start && intCmp(array[j - 1], tmp) > 0)
            {
                array[j] = array[j - 1];
                j--;
            }
            array[j] = tmp;
        }
        out = cond_out;
    }
        return out;*/
}


static void mergeSortAux(int *array, int lo, int hi, int aux[])
{
    int n = hi - lo + 1;
    if (n <= 1)
        return;
    int mid = lo + (n + 1) / 2;
    
    mergeSortAux(array, lo, mid - 1, aux);
    mergeSortAux(array, mid, hi, aux);
    merge(array, lo, mid, hi, aux);
}

void static fusion(int *array, Stack* stack,size_t length){
    /*
    //réarrangement par fusion des sous tableaux avec les =/= cas comme dans pdf
    for (int k = (length - 1); k > 0; --k)
    {
        if (k >= 2)
        {
            if (lgs[k - 2] <= lgs[k - 1] + lgs[k])
            {
                if (lgs[k] >= lgs[k - 2])
                {
                    indexs[k - 2][1] = indexs[k - 1][1];
                    lgs[k - 2] += lgs[k - 1];
                    mergeSortAux(array, indexs[k - 2][0], indexs[k - 2][1], aux);

                    indexs[k - 1][0] = indexs[k][0];
                    indexs[k - 1][1] = indexs[k][1];
                    lgs[k - 1] = lgs[k];
                }
                else if (lgs[k] < lgs[k - 2])
                {
                    indexs[k - 1][1] = indexs[k][1];
                    lgs[k - 1] += lgs[k];
                    mergeSortAux(array, indexs[k - 1][0], indexs[k - 1][1], aux);
                }
            }
            else if(lgs[k - 1] < lgs[k])
            {
                indexs[k - 1][1] = indexs[k][1];
                lgs[k - 1] += lgs[k];
                mergeSortAux(array, indexs[k - 1][0], indexs[k - 1][1], aux);
            }
        }
        else
        {
            indexs[k - 1][1] = indexs[k][1];
            lgs[k - 1] += lgs[k];
            mergeSortAux(array, indexs[k - 1][0], indexs[k - 1][1], aux);
        }
    }*/
    

    StackElement temp_A;
    StackElement temp_B;
    StackElement temp_C;
    int aux[length];

    int temp_A_start;
    int temp_B_start;
    int temp_C_start;

    int temp_A_end;
    int temp_B_end;
    int temp_C_end;

    int size_temp_A;
    int size_temp_B;
    int size_temp_C;

    int i = length;
    
    
    //int work = 1;
    //if(stack->top < 2){
        //work = 0;
    //}

    //while(work == 1){
    if(stack->top < 2){
        i = 1;
    }
    
    for(; i >1; i--){
        
        //i++;
        //printf("je rentre dans la fusion pour la %d fois\n",i);
    
        //for (int k = (length - 1); k > 0; --k){
        //work = 0;
        temp_C = pop(stack);
        temp_B = pop(stack);
        temp_A = pop(stack);
        
            
        temp_A_start = temp_A.start;
        temp_B_start = temp_B.start;
        temp_C_start = temp_C.start;

        temp_A_end = temp_A.end;
        temp_B_end = temp_B.end;
        temp_C_end = temp_C.end;

        size_temp_A = temp_A_end - temp_A_start;
        size_temp_B = temp_B_end - temp_B_start;
        size_temp_C = temp_C_end - temp_C_start;

        if(size_temp_A <= size_temp_B + size_temp_C){
            if(size_temp_A < size_temp_C){
                //work = 1;
                //fusion A et B

                mergeSortAux(array,temp_A_start,temp_B_end,aux);
                push(stack,temp_A_start,temp_B_end);
                push(stack,temp_C_start,temp_C_end);
            }else{
                //work = 1;
                //fusion B et C

                mergeSortAux(array,temp_B_start,temp_C_end,aux);
                push(stack,temp_A_start,temp_A_end);
                push(stack,temp_B_start,temp_C_end);
            }
        }else if(size_temp_B <= size_temp_C){
            //work = 1;
            //fusion B et C

            mergeSortAux(array,temp_B_start,temp_C_end,aux);
            push(stack,temp_A_start,temp_A_end);
            push(stack,temp_B_start,temp_C_end);
        }

        
        //if(stack->top < 2){
            //work = 0;
        //}
    }

    //printf("je me tire de la boucle\n");


    if(stack->top > 0){
        //printf("je fusionne les reste\n");
        //print_stack(stack);

        temp_B = pop(stack);
        temp_A = pop(stack);

        temp_A_start = temp_A.start;
        temp_B_end = temp_B.end;

        mergeSortAux(array,temp_A_start,temp_B_end,aux);
        //print_stack(stack);
        push(stack,temp_A_start,temp_B_end);
    }
    //print_stack(stack);
    //printf("fini la fusion\n");
}

void static adaptiveMerge_sort(int *array, Stack* stack,size_t length){
    size_t start = 0;
    size_t end = 0;
    int minSize = 5;
    
    /*
    for (size_t i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");*/
    //clock_t begin = clock();
    //printf("fin print\n");



    for(size_t i = 0; i < length-1; i++){
        //printf("je rentre pour la %ld dans findrun\n",i);
        //print_stack(stack);
		end = findRun(array, i, length, minSize);
        //printf("fin findrun\n");
		//printf("start adap = %ld\n",start);
        //printf("end adap = %ld\n",end);
		push(stack,start,end);
        i = end;
        start = end+1;
        //printf("je rentre pour la %ld dans fusion\n",i);
        //printf("fin push\n");
        fusion(array,stack,end);
        //printf("fin fusion\n");
        //print_stack(stack);
	}


    if(stack->top > 0){
        //printf("je fusionne les reste\n");
        //print_stack(stack);
        
        StackElement temp_A;
        StackElement temp_B;
    

        int temp_A_start;
        int temp_B_end;

        int aux[length];
        

        temp_B = pop(stack);
        temp_A = pop(stack);

        temp_A_start = temp_A.start;
        temp_B_end = temp_B.end;

        mergeSortAux(array,temp_A_start,temp_B_end,aux);
        //print_stack(stack);
        push(stack,temp_A_start,temp_B_end);
    }
    /*
    for (size_t i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");*/
}


void sort(int *array, size_t length){

    void resetCounter();
    Stack* stack = createStack(length);
    adaptiveMerge_sort(array,stack,length);
    deleteStack(stack);

}

