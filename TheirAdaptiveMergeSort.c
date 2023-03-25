/* ========================================================================= *
 * AdaptiveMergeSort
 * Implementation of the Adaptive Merge Sort algorithm.
 * ========================================================================= */
#include <stdlib.h>
#include <stddef.h>

#include "Sort.h"
#include "Array.h"

void merge(int tab[], int lo, int mid, int hi, int aux[]);
void mergeSortAux(int tab[], int lo, int hi, int aux[]);
int findRun(int *a, size_t start, size_t end, size_t minSize);

/* ========================================================================= *
 * Merge sort 
 * ========================================================================= */

// Used to merge the sub arrays (already sorted) together
void merge(int tab[], int lo, int mid, int hi, int aux[])
{
    int i = lo, j = mid;

    for (int k = lo; k <= hi; k++)
        if (i == mid)
            aux[k] = tab[j++];
        else if (j == hi + 1)
            aux[k] = tab[i++];
        else if (intCmp(tab[i], tab[j]) < 0)
            aux[k] = tab[i++];
        else
            aux[k] = tab[j++];

    for (int k = lo; k <= hi; k++)
        tab[k] = aux[k];
}

void mergeSortAux(int tab[], int lo, int hi, int aux[])
{
    int n = hi - lo + 1;
    if (n <= 1)
        return;
    int mid = lo + (n + 1) / 2;
    mergeSortAux(tab, lo, mid - 1, aux);
    mergeSortAux(tab, mid, hi, aux);
    merge(tab, lo, mid, hi, aux);
}

/* ========================================================================= *
 * FindRun
 * ========================================================================= */

// Verify if the given array is sorted (ascending or descending order) between start and start + minSize or start and end if 
// start + minSize is greater than end (they're all indexes).
// Return the last index taken in charge by the function, this following sub array is now sorted 
int findRun(int *a, size_t start, size_t end, size_t minSize)
{
    size_t index_fin_tri = start;

    // output variable and condition defining if an insertrion sort is needed (start + minSize > already sorted sub array)
    size_t cond_out = 0, out = 0;

    // define if the sub array is ascending or decreasing
    int flag_inv = 0;

    // search of the last index where the given sub array is already sorted (ascending or descending order)
    for (size_t i = start; i < end; ++i)
    {
        if (i == start && a[i] > a[i + 1])
            flag_inv = 1;

        if (a[i] <= a[i + 1] && flag_inv == 0)
            index_fin_tri++;
        else if (a[i] > a[i + 1] && flag_inv == 1)
            index_fin_tri++;
        else
            break;
    }

    // searching if the output condition si either start + minSize or end, if the latter is smaller than start + minSize
    if ((start + minSize - 1) > end)
        cond_out = end;
    else
        cond_out = (start + minSize - 1);

    // if decreasing sub array, putting it back in an ascending order
    if (flag_inv == 1)
    {
        int tmp = 0;
        size_t k = start, l = index_fin_tri;

        while(k < l)
        {
            tmp = a[k];
            a[k] = a[l];
            a[l] = tmp;
            k++;
            l--;
        }
    }

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
            tmp = a[i];
            j = i;
            // place tmp at the right position
            while (j > start && intCmp(a[j - 1], tmp) > 0)
            {
                a[j] = a[j - 1];
                j--;
            }
            a[j] = tmp;
        }
        out = cond_out;
    }
    return out;
}

/* ========================================================================= *
 * Adaptativ Merge Sort
 * ========================================================================= */

void sort(int *array, size_t length)
{
    // pile avec les indexs de debut et fin
    int **indexs = (int **)malloc(length * sizeof(int *));
    for (size_t j = 0; j < length; ++j)
    {
        indexs[j] = (int *)malloc(2 * sizeof(int));        
    }

    // tab qui contient les longueurs de ces tableaux
    int *lgs = malloc(length * sizeof(int));

    // iterateur et nbr de sous tableaux découpés et réarrangés (k)
    size_t i = 0, j = 0, k = 0;

    //découpage en sous tableaux et mise en place de la pile + tailles
    int aux[length - 1];

    while(i < length)
    {
        j = i;

        indexs[k][0] = i;
        i = findRun(array, j, length - 1, 2);
        indexs[k][1] = i;

        lgs[k] = (indexs[k][1] - indexs[k][0]) + 1;

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
                    k--;
                }
                else if (lgs[k] < lgs[k - 2])
                {
                    indexs[k - 1][1] = indexs[k][1];
                    lgs[k - 1] += lgs[k];
                    mergeSortAux(array, indexs[k - 1][0], indexs[k - 1][1], aux);
                    k--;
                }
            }
            else if(lgs[k - 1] <= lgs[k])
            {
                indexs[k - 1][1] = indexs[k][1];
                lgs[k - 1] += lgs[k];
                mergeSortAux(array, indexs[k - 1][0], indexs[k - 1][1], aux);
                k--;
            }
        }
        else if (k == 1 && lgs[k - 1] <= lgs[k])
        {
            indexs[k - 1][1] = indexs[k][1];
            lgs[k - 1] += lgs[k];
            mergeSortAux(array, indexs[k - 1][0], indexs[k - 1][1], aux);
            k--;
        }
        i++;
        k++;
    }

    k -= 1;

    if (k >= 1)
    {
        for (int l = k; l > 0; l--)
        {
            indexs[l - 1][1] = indexs[l][1];
            lgs[l - 1] += lgs[l];
            mergeSortAux(array, indexs[l - 1][0], indexs[l - 1][1], aux);
        }
    }

    // free les mallocs des variables pour la pile et les longueurs
    for (size_t i = 0; i < length; ++i)
    {
        free(indexs[i]);
    }
    free(indexs);
    free(lgs);

    return;
}
