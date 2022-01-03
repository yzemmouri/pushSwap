#include "push_swap.h"

int main(int ac, char **av)
{
    int i;
    t_stack a;
    t_stack b;

    i = ac - 1;
    if (ac < 2)
        return (0);
    else
    {
        a.tab = (int *)malloc((ac - 1) * sizeof(int));
        a.top = -1;
        b.tab = (int *)malloc((ac - 1) * sizeof(int));
        b.top = -1;
        while (i > 0)
        {
            is_valid_args(av[i]);
            a.tab[ac - i - 1] = ft_atoi(av[i]);
            ++a.top;
            is_doubling(a);
            --i;
        }
    }
    if (is_sorted_array(a.tab, ac - 2))
        return (0);
    else
    {
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