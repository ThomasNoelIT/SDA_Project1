/* ========================================================================= *
 * HeapSort
 * Implementation of the HeapSort algorithm.
 * ========================================================================= */

#include "Sort.h"
#include "Array.h"
#include "stdio.h"
#include "pthread.h"
#include <stdlib.h>

/*struct HeapifyArgs {
    int* arr;  // Pointeur vers le tableau d'entiers
    int n;     // Taille du sous-tableau à trier
    int i;     // Indice de l'élément à partir duquel exécuter maxHeapify
};*/


//fonction de base : swap les pointeurs des éléments
void static swap(int *var1, int *var2) {        
    int temporary_var;
    temporary_var = *var1;
    *var1 = *var2;
    *var2 = temporary_var;
}


//récursif
static void maintain_ownership(int *array, size_t length, int i){
    int node = i;
    int left = 2*i+1;
    int right = 2*i+2;

    while (left < (int)length && array[node] < array[left]){
        node = left;
    }

    while (right < (int)length && array[node] < array[right]){
        node = right;
    }

    if (node != i) {
        swap(&array[i], &array[node]);
        maintain_ownership(array, length, node);
    }
}

static void build_max_tree(int *array, size_t length){
    for(int i = length/2-1; i >= 0; i--){
        maintain_ownership(array, length, i);
    }
}

void sort(int *array, size_t length)
{
    build_max_tree(array, length);

    for(int i = length-1; i > 0; i--){
        swap(&array[0], &array[i]);
        maintain_ownership(array, i, 0);
    }
}
/*
void static maintain_ownership(int *array, size_t length, int i) {
    int node = i;
    int left = 2*i+1;
    int right = left+1;

    if (left < (int)length && array[node] < array[left]) {
        node = left;
    }

    if (right < (int)length && array[node] < array[right]) {
        node = right;
    }

    if (node != i && array[node] != 0) {
        swap(&array[i], &array[node]);
        maintain_ownership(array, length, node);
    }
}

void static build_max_tree(int *array, size_t length) {
    for(int i = (int)(length/2)-1; i >= 0; i--){
        maintain_ownership(array, length, i);
    }
}

void sort(int *array, size_t length) {
    build_max_tree(array, length);

    for(int i = length-1; i > 0; i--) {
        swap(&array[0], &array[i]);
        maintain_ownership(array, i, 0);
    }
}*/



/*
//mal rangé
void static maintain_ownership(int *array,size_t length, int i){
    int node = i;
    int left = 2*i+1;
    int right = left+1;
    int temporary_var;

    printf("19\n");
    printf("length = %ld\n",length);
    printf("i = %d\n",i);
    printf("left = %d\n",left);
    printf("right = %d\n",right);

    printf("20\n");
    while (left < (int)length) {
        printf("21\n");

        for (int j = 0; j < (int)length; j++) {
            printf("%d ", array[j]);
        }
        printf("\n");

        printf("length = %ld\n",length);
        printf("i = %d\n",i);
        printf("left = %d\n",left);
        printf("right = %d\n",right);
        if(left <= (int)length && array[node]<array[left]){
        node = left;
        }
        printf("22\n");
        
        if(right <= (int)length && array[node]<array[right]){
            node = right;
        }
        printf("23\n");

        if (node != i) {
            printf("24\n");
            temporary_var = array[i];
            array[i] = array[node];
            array[node] = temporary_var;

            i = node;
            left = 2*i + 1;
            right = left +1;
        }
        else {
            printf("25\n");
            break;
        }
        printf("26\n");
    }
}
*/


/*
//maintient sa propriété 
//mal rangé
//si arbre pas complet
void static maintain_ownership(int *array,size_t length, int i){
    int node = i;
    int left = 2*i+1;
    int right = left+1;
    //int temporary_var = i;

    printf("length = %ld\n",length);
    printf("i = %d\n",i);
    printf("left = %d\n",left);
    printf("right = %d\n",right);
    //printf("temporary_var = %d\n",temporary_var);
    printf("array[i] = %d\n",array[i]);
    printf("array[left] = %d\n",array[left]);
    printf("array[right] = %d\n",array[right]);
    
    for (int i = 0; i < (int)length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    

    printf("20\n");

    if(left <= (int)length && array[node]<array[left]){
        node = left;
    }
    printf("21\n");
    if(right <= (int)length && array[node]<array[right]){
        node = right;
    }
    printf("22\n");

    printf("i after = %d\n",i);
    printf("node after = %d\n",node);

    if(node != i && array[node] !=0){
        swap(&array[i],&array[node]);
    }
    
    if ((int)(length/2)-1 != 0){
        maintain_ownership(array,length,node);
    }
    
    
    printf("23\n");
}*/



/*
//construit l'arbre maximum en utilisant la propriété 
void static build_max_tree(int *array, size_t length){
    printf("10\n");
    printf("length = %ld\n",length);
    for(int i = 0; i < (int)length-1;i++){
        printf("11\n");
        maintain_ownership(array,i,0);
        printf("12\n");
    }
    printf("13\n");
    
    for (int i = 0; i < (int)length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
}


void sort(int *array, size_t length)
{
    // To be completed
    //2 phases : créer un arbre max et maintenir sa propriété lors de la décharge
    for (int i = 0; i < (int)length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("1\n");
    build_max_tree(array,length);
    printf("2\n");

    for(int i = length-1;i>=0;i--){
        printf("4\n");
        swap(&array[0],&array[i]);
        printf("5\n");
        maintain_ownership(array,i,0);
        printf("6\n");
    }
    printf("3\n");
    for (int i = 0; i < (int)length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}*/



/*
void* maxHeapify(void* arg) {
    struct HeapifyArgs* args = (struct HeapifyArgs*) arg;
    int* arr = args->arr;
    int n = args->n;
    int i = args->i;

    int largest = i; // Indice de l'élément le plus grand
    int l = 2*i + 1; // Indice de l'enfant gauche
    int r = 2*i + 2; // Indice de l'enfant droit

    // Si l'enfant gauche est plus grand que le noeud racine
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Si l'enfant droit est plus grand que le noeud racine
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Si l'élément le plus grand n'est pas la racine
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Appel récursif à maxHeapify sur le sous-arbre affecté
        struct HeapifyArgs leftArgs = { arr, n, largest };
        maxHeapify(&leftArgs);
    }

    return NULL;
}

void sort(int *array, size_t length)
{
    // To be completed
    //2 phases : créer un arbre max et maintenir sa propriété lors de la décharge
    int numThreads = 4;
    
    build_max_tree(array,length);

    for(int i = length-1;i>=0;i--){
        swap(&array[0],&array[i]);
        maintain_ownership(array,length,0);
    }
    
   for (int i = length / 2 - 1; i >= 0; i--)
        maxHeapify((void*) &(struct HeapifyArgs) { array, length, i });

   for (int i = length-1; i >= 0; i--) {
        // Échanger l'élément en cours de traitement avec l'élément à la fin du tableau
        swap(&array[0], &array[i]);

        // Exécuter maxHeapify sur la partie non triée du tableau
        int chunkSize = (i+1) / numThreads;
        pthread_t threads[numThreads];
        for (int t = 0; t < numThreads; t++) {
            int start = t * chunkSize;
            int end = (t == numThreads-1) ? i : (t+1)*chunkSize - 1;
            struct HeapifyArgs* args = (struct HeapifyArgs*) malloc(sizeof(struct HeapifyArgs));
            args->arr = array+start;
            args->n = end-start+1;
            args->i = 0;
            pthread_create(&threads[t], NULL, maxHeapify, (void*) args);
        }
    }

   
    return;
}*/
