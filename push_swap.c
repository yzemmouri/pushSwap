#include "push_swap.h"

int main(int ac, char **av)
{
    int i;
    t_indexed_stack a;
    t_indexed_stack b;

    i = ac - 1;
    if (ac < 2)
        return (0);
    else
    {
        a.tab = (t_indexed_value *)malloc((ac - 1) * sizeof(t_indexed_value));
        a.top = -1;
        b.tab = (t_indexed_value *)malloc((ac - 1) * sizeof(t_indexed_value));
        b.top = -1;
        while (i > 0)
        {
            is_valid_args(av[i]);
            a.tab[ac - i - 1].value = ft_atoi(av[i]);
            a.tab[ac - i - 1].index = ac - i - 1;
            ++a.top;
            is_doubling_indexed(a);
            --i;
        }
    }
 i = 0;
    while (i < ac - 1)
    {
        printf("%d-->%d\n", a.tab[i].index, a.tab[i].value);
        ++i;
    }
    printf("\n\n");
    mergeSort(a.tab, 0, ac - 2, 1);

    i = 0;
    while (i < ac - 1)
    {
        a.tab[i].value = i;
        ++i;
    }
     i = 0;
    while (i < ac - 1)
    {
        printf("%d-->%d\n", a.tab[i].index, a.tab[i].value);
        ++i;
    }
    printf("\n\n");
    mergeSort(a.tab, 0, ac - 2, 0);

    i = 0;
    while (i < ac - 1)
    {
        printf("%d-->%d\n", a.tab[i].index, a.tab[i].value);
        ++i;
    }

    if (is_sorted_indexed_array(a.tab, ac - 2))
        return (0);
    else
    {   
        if (ac - 1 == 3)
        {

        }
        if (ac - 1 <= 5)
        {

        }
        else if (ac - 1 <= 100)
        {

        }
        else if (ac - 1 <= 500)
        {
            
        }
    }
    return (0);
}