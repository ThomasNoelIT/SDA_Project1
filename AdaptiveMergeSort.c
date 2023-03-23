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
    stack->top = 0;
    return stack;
}

// Vérifie si la pile est vide
static int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Vérifie si la pile est pleine
static int isFull(Stack* stack) {
    return stack->top == stack->max_size;
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

static void print_stack(struct Stack* s) {
    int i;
    if (isEmpty(s)) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements:\n");
        for (i = s->top; i >= 0; i--) {
            printf("start = %ld, end = %ld\n", s->data[i].start,s->data[i].end);
        }
    }
}


// Libère la mémoire allouée pour la pile
static void deleteStack(Stack* stack) {
    free(stack->data);
    free(stack);
}




/*
typedef struct Stack {
    int Max_Size;
    int* data; // Tableau qui contient les éléments de la pile
    int top; // Indice de sommet de pile
} Stack;

// Fonction pour créer une pile vide
static Stack* createStack(size_t size) {
    Stack* stack = (Stack*) malloc(sizeof(Stack)); // Alloue la mémoire pour la pile
    stack->Max_Size = size;
    stack->data = (int*) malloc(sizeof(int) * size); // Alloue la mémoire pour le tableau de données de la pile
    stack->top = -1; // Initialise l'indice de sommet de pile à -1
    return stack;
}

// Fonction pour empiler un entier dans la pile
static void push(Stack* stack, int element) {
    if (intCmp(stack->top, stack->Max_Size - 1) == 0) {
        printf("error1\n");
    } else {
        stack->top++;
        stack->data[stack->top] = element;
    }
}

// Fonction pour dépiler un entier de la pile
static int pop(Stack* stack) {
    if (intCmp(stack->top, -1) == 0) {
        printf("error2\n");
        return -1;
    } else {
        int element = stack->data[stack->top];
        stack->top--;
        return element;
    }
}*/

/*
static void display(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements:\n");
        int i;
        for (i = stack->top; i >= 0; i--) {
            printf("%d ", stack->data[i]);
        }
        printf("\n");
        printf("nbr data ds la pile = %d \n",stack->top);
        printf("top pile = %d \n",stack->top);
    }
}*/






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

static void merge(int tab[], int lo, int mid, int hi, int aux[])
{
    int i = lo, j = mid;

    for (int k = lo; k <= hi; k++){
        if (i == mid)
            aux[k] = tab[j++];
        else if (j == hi + 1)
            aux[k] = tab[i++];
        else if (intCmp(tab[i], tab[j]) < 0)
            aux[k] = tab[i++];
        else
            aux[k] = tab[j++];
    }
    for (int k = lo; k <= hi; k++){
        tab[k] = aux[k];
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
    //size_t length = last+start;
    size_t length = last;
    size_t i;

    int temp1 = array[start];
    int temp2 = 0;

    //printf("length = %ld\n",length);

    int flag_state = 0;
    for(i = start; i < length; i++){
        //printf("start = %ld\n",start);
        //printf("end = %ld\n",end);
        temp2 = array[i+1];
        if(i+1 < last){
            //printf("state = %d\n",state);
            
            if(i == start && intCmp(temp1, temp2) > 0){
                flag_state = 1;
            }

            if(flag_state == 0){
                if(intCmp(temp1, temp2) < 0){
                    end++;
                }

                if(intCmp(temp1, temp2) > 0){
                    
                    //if(i < minSize){
                        //insertion(array,start,minSize);
                        //end = start+minSize;
                    //}
                    break;
                }
            }else if(flag_state == 1){
                if(intCmp(temp1, temp2) > 0){
                    end++;
                }
                if(intCmp(temp1, temp2) < 0){
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

/*
void fusion(int* tableau1, int taille1, int* tableau2, int taille2, int* resultat) {
    int i = 0, j = 0, k = 0;
    
    // Parcours les deux tableaux en comparant les éléments et en les fusionnant
    while (i < taille1 && j < taille2) {
        if (tableau1[i] < tableau2[j]) {
            resultat[k++] = tableau1[i++];
        } else {
            resultat[k++] = tableau2[j++];
        }
    }
    
    // Ajoute les éléments restants du premier tableau
    while (i < taille1) {
        resultat[k++] = tableau1[i++];
    }
    
    // Ajoute les éléments restants du deuxième tableau
    while (j < taille2) {
        resultat[k++] = tableau2[j++];
    }
}*/

void static fusion(int *array, Stack* stack,size_t length){
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

    int n;
    int mid;

    int work = 1;
    if(stack->top < 2){
        work = 0;
    }

    while(work == 1){
        work = 0;
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
                    work = 1;
                    //fusion A et B
                    n = temp_B_end - temp_A_start + 1;
                    if (n <= 1)
                        return;
                    mid = temp_A_start + (n + 1) / 2;

                    merge(array,temp_A_start,mid,temp_B_end,aux);
                    push(stack,temp_A_start,temp_B_end);
                    push(stack,temp_C_start,temp_C_end);
                }else{
                    work = 1;
                    //fusion B et C
                    n = temp_C_end - temp_B_start + 1;
                    if (n <= 1)
                        return;
                    mid = temp_B_start + (n + 1) / 2;

                    merge(array,temp_B_start,mid,temp_C_end,aux);
                    push(stack,temp_A_start,temp_A_end);
                    push(stack,temp_B_start,temp_C_end);
                }
            }else if(size_temp_B <= size_temp_C){
                work = 1;
                //fusion B et C
                n = temp_C_end - temp_B_start + 1;
                    if (n <= 1)
                        return;
                mid = temp_B_start + (n + 1) / 2;

                merge(array,temp_B_start,mid,temp_C_end,aux);
                push(stack,temp_A_start,temp_A_end);
                push(stack,temp_B_start,temp_C_end);
            }

    }
}

/*
void static fusion(int *array, Stack* stack,size_t length){

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

    int n;
    int mid;



    while (stack->top > 0){
       
        if (stack->top > 1){

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
                    //fusion A et B
                    n = temp_B_end - temp_A_start + 1;
                    if (n <= 1)
                        return;
                    mid = temp_A_start + (n + 1) / 2;

                    merge(array,temp_A_start,mid,temp_B_end,aux);
                    push(stack,temp_A_start,temp_B_end);
                    push(stack,temp_C_start,temp_C_end);
                }else{
                    //fusion B et C
                    n = temp_C_end - temp_B_start + 1;
                    if (n <= 1)
                        return;
                    mid = temp_B_start + (n + 1) / 2;

                    merge(array,temp_B_start,mid,temp_C_end,aux);
                    push(stack,temp_A_start,temp_A_end);
                    push(stack,temp_B_start,temp_C_end);
                }
            }else if(size_temp_B <= size_temp_C){
                //fusion B et C
                n = temp_C_end - temp_B_start + 1;
                    if (n <= 1)
                        return;
                mid = temp_B_start + (n + 1) / 2;

                merge(array,temp_B_start,mid,temp_C_end,aux);
                push(stack,temp_A_start,temp_A_end);
                push(stack,temp_B_start,temp_C_end);
            }
        }else{
            temp_B = pop(stack);
            temp_A = pop(stack);

            n = temp_B_end - temp_A_start + 1;
                    if (n <= 1)
                        return;
            mid = temp_A_start + (n + 1) / 2;

            merge(array,temp_A_start,mid,temp_B_end,aux);
            push(stack,temp_A_start,temp_B_end);
        }
    }
}*/

/*
void static fusion(int *array, Stack* stack){

    if (stack->top <= 1) {
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
            //fusion A et B
            merge(array,temp_A_start,temp_B_end);
            push(stack,temp_A_start,temp_B_end);
            push(stack,temp_C_start,temp_C_end);
        }else{
            //fusion B et C
            merge(array,temp_B_start,temp_C_end);
            push(stack,temp_A_start,temp_A_end);
            push(stack,temp_B_start,temp_C_end);
        }
    }else if(size_temp_B <= size_temp_C){
        //fusion B et C
        insertion(array,temp_B_start,temp_C_end);
        push(stack,temp_A_start,temp_A_end);
        push(stack,temp_B_start,temp_C_end);
    }

    fusion(array, stack);
}*/

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

    for(size_t i = 0; i < length; i++){
        //print_stack(stack);
		end = findRun(array, i, length, minSize);
        //printf("fin findrun\n");
		//printf("start adap = %ld\n",start);
        //printf("end adap = %ld\n",end);
		push(stack,start,end);
        i = end;
        start = end+1;
        //printf("fin push\n");
        fusion(array,stack,end);
        //printf("fin fusion\n");
        //print_stack(stack);
	}
    if(stack->top > 0){
        int n;
        int mid;
        int aux[length];
    

        StackElement temp_A;
        StackElement temp_B;
        int temp_A_start;
        int temp_B_end;


        temp_B = pop(stack);
        temp_A = pop(stack);

        temp_A_start = temp_A.start;
        temp_B_end = temp_B.end;

        n = temp_B_end - temp_A_start + 1; 
        if (n <= 1)
            return;
        mid = temp_A_start + (n + 1) / 2;

        merge(array,temp_A_start,mid,temp_B_end,aux);
        push(stack,temp_A_start,temp_B_end);
    }
    //printf("fin code\n");

    //printf("array length -1 = %d\n",array[length-1]);
    /*
    clock_t finish = clock();
    unsigned long millis = (finish -  begin) * 1000 / CLOCKS_PER_SEC;
    printf( "findrun finish in %ld ms\n", millis );  */
    //print_stack(stack);

    /*
    for (size_t i = 0; i < length; i++) {
        //printf("i = %ld\n",i);
        printf("%d ", array[i]);
    }
    printf("\n");*/
    
    
    //begin = clock();

    

    

    /*
    finish = clock();
    millis = (finish -  begin) * 1000 / CLOCKS_PER_SEC;
    printf( "fusion finish in %ld ms\n", millis );  */

    /*
    for (size_t i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");*/
    
}


/*
//A PRENDRE SI LES PILES SONT AUTORISEES
void static fusion(int *array, Stack* stack_result_findRun,size_t length){

	int end = 0;
	double nb_array = length/4; //0.1 for 10 | 0.01 for 100 | 0.025 for 40 | 0.02 for 50 arrays
	long double preMinSize = length/nb_array;
	int minSize = (int) preMinSize;

    int temp1;
    int temp2;
    int temp3;
    int temp4;

    int temp[3];

    int size_temp1;
    int size_temp2;
    int size_temp3;

    //printf("10\n");
    //printf("length = %ld \n",length);
    //display(stack_result_findRun);

    for(size_t i = 0; i < length; i++){
		end = findRun(array, i, length-1, minSize);
		i = end;
        //printf("end =%d \n",end);
		push(stack_result_findRun ,end);
	}

    //printf("11\n");

    //display(stack_result_findRun);

    //printf("12\n");

    //gérer le cas nb_array<2
	while (stack_result_findRun->top > 0){

        //printf("13\n");
		//int j = 0;
		if (intCmp(stack_result_findRun->top, 2) > 0){ //nb_array must have a value of 3 to be able to compute the following if
            //printf("14\n");
            //display(stack_result_findRun);
            temp1 = pop(stack_result_findRun);
            temp2 = pop(stack_result_findRun);
            temp3 = pop(stack_result_findRun);
            temp4 = pop(stack_result_findRun);//dépassement tab

            size_temp1 = temp1-temp2;
            size_temp2 = temp2-temp3;
            size_temp3 = temp3 - temp4;
            
            
            //printf("15\n");
			if (size_temp3 <= size_temp2+size_temp1){
                //printf("16\n");
                //temp = temp1;
                if(size_temp1 < size_temp3){
                    //fusion temp2 et temp1

                    insertion(array, temp3, temp1);
                    push(stack_result_findRun,temp4);
                    push(stack_result_findRun,temp3);
                    push(stack_result_findRun,temp1);
                    
                }else{
                    //fusion temp2 et temp3

                    insertion(array, temp4, temp2);
                    push(stack_result_findRun,temp4);
                    push(stack_result_findRun,temp2);
                    push(stack_result_findRun,temp1);
                }
				
				
                //printf("17\n");
    		}else{ //error
            //printf("19\n");
            
			//fusionner temp1 et temp2
			insertion(array, temp3, temp1);
            push(stack_result_findRun,temp4);
            push(stack_result_findRun,temp3);
            push(stack_result_findRun,temp1);
			
            //printf("20\n");
		    }
            //printf("18\n");
		}else{
            
            //reverse_stack(stack_result_findRun,stack_result_findRun->top);
            
            //printf("10\n");
            //for(int i = 0; i < stack_result_findRun->top;i++){
                //printf("11\n");
                //temp[i] = pop(stack_result_findRun);
                //temp[i+1] = pop(stack_result_findRun);
                //if(temp[i+1]==-1){
                    //break;
                //}
                //insertion(array, temp[i], temp[i+1]);
                //push(stack_result_findRun,temp[i]);
            //} 
            printf("12\n");
            //printf("\n");
            
            
            //printf("19\n");
            temp1 = pop(stack_result_findRun);
            temp2 = pop(stack_result_findRun);
            temp3 = pop(stack_result_findRun);

            if(stack_result_findRun->top != -1){
                printf("pile is not empty");
            }

			
			insertion(array, 0, temp1);
            push(stack_result_findRun,temp1);
			
            //printf("20\n");
		}
        //printf("21\n");
    }
    //printf("22\n");
    //display(stack_result_findRun);

    
}*/






//-----------------------------------------------------------------------------------//
//sans findrun

/*
#define INSERTION_SORT_THRESHOLD 10

static void merge(int arr[], int left[], int left_size, int right[], int right_size) {
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left_size) {
        arr[k++] = left[i++];
    }
    while (j < right_size) {
        arr[k++] = right[j++];
    }
}

static void merge_sort(int arr[], int n) {
    if (n <= 1) {
        return;
    }
    if (n <= INSERTION_SORT_THRESHOLD) {
        // Utilisation de l'algorithme d'insertion sort pour les petits sous-tableaux
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    } else {
        int mid = n / 2;
        int* left = (int*) malloc(mid * sizeof(int));
        int* right = (int*) malloc((n - mid) * sizeof(int));
        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        for (int i = mid; i < n; i++) {
            right[i - mid] = arr[i];
        }
        merge_sort(left, mid);
        merge_sort(right, n - mid);
        merge(arr, left, mid, right, n - mid);
        free(left);
        free(right);
    }
}
*/


//-----------------------------------------------------------------------------------//
//avec findrun

/*
static int findRun(int *array, int start,int last, int minSize) {
    int end = start + 1;
    int n = last-start;
        
    //printf("20\n");

    // Trouver la fin du sous-tableau trié croissant
    while (end < n && array[end] >= array[end-1])
        end++;
    //printf("21\n");
    // Si la longueur du sous-tableau trié est inférieure à minSize
    if (end - start < minSize) {
        //printf("22\n");
        // Insérer les éléments suivants dans le sous-tableau trié
        for (int i = start + 1; i < end; i++) {
            //printf("23\n");
            int key = array[i];
            int j = i - 1;
            while (j >= start && array[j] > key) {
                //printf("24\n");
                array[j+1] = array[j];
                j--;
            }
            //printf("25\n");
            array[j+1] = key;
        }
    }
    // Si le sous-tableau trié est dans l'ordre inverse
    else if (array[start] > array[end-1]) {
        //printf("26\n");
        swap(array+start, array+end);
    }
    //printf("27\n");
    // Renvoyer la fin du sous-tableau trié
    return end-1;
}

// Fonction de fusion de deux sous-tableaux triés de A
static void merge(int *array, int start, int mid, int end) {
    int p = start, q = mid+1;
    int B[end-start+1], k = 0;
    
    //printf("10\n");
    // Fusionner les deux sous-tableaux triés en un tableau trié
    for (int i = start; i <= end; i++) {
        //printf("11\n");
        if (p > mid)
            B[k++] = array[q++];
        else if (q > end)
            B[k++] = array[p++];
        else if (array[p] <= array[q])
            B[k++] = array[p++];
        else
            B[k++] = array[q++];
    }
    //printf("12\n");
    
    // Copier le tableau trié dans A
    for (int i = 0; i < k; i++)
        array[start+i] = B[i];
    //printf("13\n");
}

// Fonction principale de tri par fusion adaptatif de A
static void adaptiveMergeSort(int *array, int start, int end, int minSize) {
    if (start < end) {
        // Trouver le sous-tableau trié de A[start...end]
        //printf("3\n");
        int mid = findRun(array, start,end, minSize);
        //printf("4\n");
        // Fusionner les deux sous-tableaux triés de A[start...mid] et A[mid+1...end]
        adaptiveMergeSort(array, start, mid, minSize);
        //printf("5\n");
        adaptiveMergeSort(array, mid+1, end, minSize);
        //printf("6\n");
        merge(array, start, mid, end);
        //printf("7\n");
    }
}*/


void sort(int *array, size_t length){

    void resetCounter();

    //-----------------------------------------------------------------------------------//
    //sans findrun
    /*
    int minSize = 32;
    adaptiveMergeSort(array,0,length-1,minSize);



    */
    //-----------------------------------------------------------------------------------//
    //avec findrun mais lent
    /*
    merge_sort(array, length);
    */




   //-----------------------------------------------------------------------------------//
    //V1


    Stack* stack = createStack(length);
    adaptiveMerge_sort(array,stack,length);
    deleteStack(stack);

}

