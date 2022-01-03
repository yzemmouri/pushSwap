int is_sorted_array(int *a, int n)
{
    if (n == 1 || n == 0)
        return 1;
    return a[n - 1] <= a[n - 2] &&
        is_sorted_array(a, n - 1);
}