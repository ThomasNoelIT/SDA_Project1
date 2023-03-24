/* ========================================================================= *
 * AdaptiveMergeSort
 * Implementation of the Adaptive Merge Sort algorithm.
 * ========================================================================= */

#include "Sort.h"
#include "Array.h"
#include "stdio.h"
#include <stdlib.h>

typedef struct StackElement {
    size_t start;
    size_t end;
} StackElement;

typedef struct Stack {
    int max_size;
    StackElement* data;
    int top; 
} Stack;

Stack* createStack(size_t size);
int isEmpty(Stack* stack);
int isFull(Stack* stack);
void push(Stack* stack, size_t start, size_t end);
StackElement pop(Stack* stack);
void print_stack(struct Stack* s) ;
void deleteStack(Stack* stack);

void swap(int *var1, int *var2);
void swap_array(int *array,size_t start, size_t length);
void insertion(int *array,int start, size_t length);
void merge(int* array, int lo, int mid, int hi, int aux[]);
void mergeSortAux(int *array, int lo, int hi, int aux[]);
int findRun(int *array, size_t start,size_t last, size_t minSize);
void fusion(int *array, Stack* stack,int*aux);
void adaptiveMerge_sort(int *array,size_t length);

// Initialise une pile vide
Stack* createStack(size_t size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->max_size = size;
    stack->data = (StackElement*)malloc(sizeof(StackElement) * size);
    stack->top = 0;
    return stack;
}

// Vérifie si la pile est vide
int isEmpty(Stack* stack) {
    return stack->top == 0;
}

// Vérifie si la pile est pleine
int isFull(Stack* stack) {
    return stack->top == stack->max_size;
}

// Ajoute un élément au sommet de la pile
void push(Stack* stack, size_t start, size_t end) {
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
StackElement pop(Stack* stack) {
    StackElement d;
    if (isEmpty(stack)) {
        printf("Erreur : pile vide.\n");
        d.start = 0;
        d.end = 0;
        return d;
    }
    stack->top--;
    int top = stack->top;
    d = stack->data[top];
    stack->data[top].end = 0;
    stack->data[top].start = 0;
    return d;
}
/*void print_stack(struct Stack* s) {
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
void deleteStack(Stack* stack) {
    if(stack == NULL){
        return;
    }
    free(stack->data);
    free(stack);
    
}



void swap(int *var1, int *var2) {        
    int temporary_var;
    temporary_var = *var1;
    *var1 = *var2;
    *var2 = temporary_var;
}

void swap_array(int *array,size_t start, size_t length) {
    size_t end = length;
    while (end > start) {
        swap(&array[start],&array[end-1]);
        start++;
        end--;
    }
}

void insertion(int *array,int start, size_t length){
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

void merge(int* array, int lo, int mid, int hi, int aux[])
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

/*
void mergeSortAux(int *array, int lo, int hi, int aux[])
{
    int n = hi - lo + 1;
    if (n <= 1)
        return;
    int mid = lo + (n + 1) / 2;
    
    mergeSortAux(array, lo, mid - 1, aux);
    mergeSortAux(array, mid, hi, aux);
    //merge(array, lo, mid, hi, aux);
}*/

//du plus petit au plus grand
int findRun(int *array, size_t start, size_t last, size_t minSize){
    
    size_t end = start;
    //size_t length = last-start;
    size_t length = last;
    size_t i;

    int temp1;
    int temp2 = array[start];

    //printf("length = %ld\n",length);

    int flag_state = 0;
    for(i = start; i < length-1; i++){
        //printf("start = %ld\n",start);
        //printf("end = %ld\n",end);

            temp1 = temp2;
            temp2 = array[i+1];
            //printf("state = %d\n",state);
            
            if(i == start && temp1 > temp2){
                flag_state = 1;
            }

            if(flag_state == 0){
                if(temp1 < temp2){
                    end++;
                }

                if(temp1 >= temp2){
                    break;
                }
            }else if(flag_state == 1){
                if(temp1 > temp2){
                    end++;
                }
                if(temp1 <= temp2){
                    break;
                }
            }else{
                break;
            }
    }
    
    if(flag_state == 1){
        swap_array(array,start,i+1);
    }

    if(start+minSize < length){
    //if(end+1-start < minSize){
        if(i-start +1 < minSize){
            //printf("je rentre car i < min size: i = %ld et minsize = %ld\n",i,minSize);
            insertion(array,i,minSize+start);
            i = start+minSize-1;
        } 
    }else{
        insertion(array,i,length);
        i = length-1;
    }
    return i;
    
}

void fusion(int *array, Stack* stack,int*aux){

    if(stack->top == 1){
        printf("le top  vaut == 1\n");
        return;  
    }

    StackElement temp_A;
    StackElement temp_B;
    StackElement temp_C;

    int temp_A_start;
    int temp_B_start;
    int temp_C_start;

    int temp_A_end;
    int temp_B_end;
    int temp_C_end;

    int size_temp_A;
    int size_temp_B;
    int size_temp_C;

    printf("10\n");
    while(1){   

        print_stack(stack);

        //printf("je rentre ds la boucle \n");
        printf("11\n");
        /*if(stack->top <= 2){
            printf("le top  vaut == 2\n");
            //printf("22\n");
            temp_A = pop(stack);
            temp_B = pop(stack);
            //printf("23\n");
            
            //printf("24\n");

            temp_A_start = temp_A.start;
            temp_B_end = temp_B.end;

            //printf("A start = %d\n", temp_A_start);
            //printf("B end = %d\n", temp_B_end);

            merge(array,temp_A_start,temp_B_start,temp_B_end,aux);
            push(stack,temp_A_start,temp_B_end);

            return;
            
        }*/

        if(stack->top >2){
            printf("12\n");


            temp_A = pop(stack);
            temp_B = pop(stack);
            temp_C = pop(stack);
        
        
        
            
            temp_A_start = temp_A.start;
            temp_B_start = temp_B.start;
            temp_C_start = temp_C.start;

            temp_A_end = temp_A.end;
            temp_B_end = temp_B.end;
            temp_C_end = temp_C.end;

            size_temp_A = temp_A_end - temp_A_start+1;
            size_temp_B = temp_B_end - temp_B_start+1;
            size_temp_C = temp_C_end - temp_C_start+1;

            printf("A start = %d\n", temp_A_start);
            printf("A end = %d\n", temp_A_end);
            printf("B start = %d\n", temp_B_start);
            printf("B end = %d\n", temp_B_end);
            printf("C start = %d\n", temp_C_start);
            printf("C end = %d\n", temp_C_end);

            printf("size_temp_A = %d\n", size_temp_A);
            printf("size_temp_B = %d\n", size_temp_B);
            printf("size_temp_C = %d\n", size_temp_C);

            //printf("12\n");
            if(size_temp_C <= size_temp_B + size_temp_A){
                //printf("14\n");
                if(size_temp_A <= size_temp_C){
                    printf("fus AB\n");
                    //printf("16\n");
                    //work = 1;
                    //fusion A et B

                    /*merge(array,temp_C_start,temp_B_start,temp_B_end,aux);
                    push(stack,temp_C_start,temp_B_end);
                    push(stack,temp_A_start,temp_A_end);*/

                    merge(array,temp_B_start,temp_A_start,temp_A_end,aux);
                    push(stack,temp_C_start,temp_C_end);
                    push(stack,temp_B_start,temp_A_end);
                
                    //printf("17\n");
                }else{
                    printf("fus BC\n");
                    //printf("18\n");
                    //work = 1;
                    //fusion B et C


                    /*merge(array,temp_B_start,temp_A_start,temp_A_end,aux);
                    push(stack,temp_C_start,temp_C_end);
                    push(stack,temp_B_start,temp_A_end);*/

                    merge(array,temp_C_start,temp_B_start,temp_B_end,aux);
                    push(stack,temp_C_start,temp_B_end);
                    push(stack,temp_A_start,temp_A_end);
                    //printf("19\n");

                }
                //printf("15\n");
            }else if(size_temp_B <= size_temp_A){
                printf("égale => fus BC\n");
                //work = 1;
                //fusion B et C
                merge(array,temp_B_start,temp_A_start,temp_A_end,aux);
                push(stack,temp_C_start,temp_C_end);
                push(stack,temp_B_start,temp_A_end);
            }else{
                printf("pas d action\n\n");
                push(stack,temp_C_start,temp_C_end);
                push(stack,temp_B_start,temp_B_end);
                push(stack,temp_A_start,temp_A_end);
            
                return;
            }
        }else if(size_temp_B <= size_temp_A){
            printf("égale => fus BC\n");
            temp_A = pop(stack);
            temp_B = pop(stack);

            temp_A_start = temp_A.start;
            temp_B_start = temp_B.start;

            temp_A_end = temp_A.end;
            temp_B_end = temp_B.end;
            //work = 1;
            //fusion B et C
            merge(array,temp_B_start,temp_A_start,temp_A_end,aux);
            push(stack,temp_B_start,temp_A_end);
            return;
        }else{
            printf("pas d action\n\n");
            return;
        }

        
        //printf("13\n");
    }
}

void adaptiveMerge_sort(int *array,size_t length){

    int minSize = 32;
    Stack* stack = createStack((int)(length/minSize)+1);
    size_t end = 0;

    int aux[length];
    for (size_t i = 0; i < length; i++) {
        printf("%d ", array[i]); // affichage de chaque élément du tableau
    }
    printf("\n");



    for(size_t i = 0; i < length; i++){
        //printf("je rentre pour la %ld dans findrun\n",i);
        
		end = findRun(array, i, length, minSize);

        
        //printf("fin findrun\n");
		//printf("start findrun = %ld\n",start);
        //&printf("end findrun = %ld\n",end);
		push(stack,i,end);
        //print_stack(stack);
        
        //printf("je rentre pour la %ld dans fusion\n",i);
        //printf("fin push\n");
        //printf("1\n");
        fusion(array,stack,aux);
        //printf("2\n");
        //printf("fin fusion\n");
        //print_stack(stack);
        i = end;
	}


    StackElement temp_A;
    StackElement temp_B;

    int temp_A_start;
    int temp_A_end;
    int temp_B_start;
    int temp_B_end;

    printf("\n");
    print_stack(stack);
    printf("\n");

    printf("top == %d\n",stack->top);

    print_stack(stack);

    while(stack->top > 1){
        printf("top == %d\n",stack->top);

       //printf("je rentre\n");
        temp_A = pop(stack);
        temp_B = pop(stack);
        printf("top == %d\n",stack->top);
        
        temp_A_start = temp_A.start;
        temp_B_start = temp_B.start;

        temp_A_end = temp_A.end;
        temp_B_end = temp_B.end;

        printf("A start = %d\n", temp_A_start);
        printf("A end = %d\n", temp_A_end);
        printf("B start = %d\n", temp_B_start);
        printf("B end = %d\n", temp_B_end);

        printf("\n");
        printf("state de la pile == %d\n",isEmpty(stack));
        print_stack(stack);
        printf("\n");

        merge(array,temp_B_start,temp_A_start,temp_A_end,aux);
        push(stack,temp_B_start,temp_A_end);
        

    }
    //merge(array,0,temp_A_start,length,aux);


    insertion(array,0,length);

    /*for (size_t i = 0; i < length; i++) {
        printf("%d ", array[i]); // affichage de chaque élément du tableau
    }
    printf("\n");*/

    deleteStack(stack);
}


void sort(int *array, size_t length){

    void resetCounter();
    adaptiveMerge_sort(array,length);
    //printf("fini\n");

}

