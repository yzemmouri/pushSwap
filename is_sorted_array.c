#include "push_swap.h"

int is_sorted_array(int *a, int n)
{
    if (n == 1 || n == 0)
        return 1;
    return a[n - 1] <= a[n - 2] &&
        is_sorted_array(a, n - 1);
}

int is_sorted_indexed_array(t_indexed_value *a, int n)
{
    if (n == 1 || n == 0)
        return 1;
    return a[n - 1].value <= a[n - 2].value &&
        is_sorted_indexed_array(a, n - 1);
}

void merge(t_indexed_value *stack, int l, int m, int r, int by_val)
{
    t_merge_tools t;
    t_indexed_value L[m - l + 1];
    t_indexed_value R[r - m];

    t.n1 = m - l + 1;
    t.n2 = r - m;
    t.i = -1;
    t.j = -1;
    while (++t.i < t.n1)
        L[t.i] = stack[l + t.i];
    while (++t.j < t.n2)
        R[t.j] = stack[m + 1 + t.j];
    t.i = 0;
    t.j = 0;
    t.k = l;
    while (t.i < t.n1 && t.j < t.n2)
    {
        if(by_val)
        {
            if (L[t.i].value <= R[t.j].value)
            {
                stack[t.k] = L[t.i];
                t.i++;
            }
            else
            {
                stack[t.k] = R[t.j];
                t.j++;
            }
        }
        else
        {
            if (L[t.i].index <= R[t.j].index)
            {
                stack[t.k] = L[t.i];
                t.i++;
            }
            else
            {
                stack[t.k] = R[t.j];
                t.j++;
            }
        }
        t.k++;
    }
    while (t.i < t.n1)
    {
        stack[t.k] = L[t.i];
        t.i++;
        t.k++;
    }
    while (t.j < t.n2)
    {
        stack[t.k] = R[t.j];
        t.j++;
        t.k++;
    }
}

void mergeSort(t_indexed_value *stack, int l, int r, int by_val)
{
    int m; 
    if (l < r)
    {
        m = l + (r - l) / 2;
        mergeSort(stack, l, m, by_val);
        mergeSort(stack, m + 1, r, by_val);
        merge(stack, l, m, r, by_val);
    }
}