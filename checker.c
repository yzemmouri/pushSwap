#include "push_swap.h"

int is_valid_sorted_stack(t_stack a, t_stack b, int a_size)
{
    if(b.top > -1)
        return (0);
    return (is_sorted_array(a.tab, a_size));
}

int main(int ac, char **av)
{
    int i;
    char *line;
    t_stack a;
    t_stack b;


    i = ac - 1;
    if (ac < 2)
    {
        printf("args empty");
        return (0);
    }
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
    while (get_next_line(1, &line))
    {
        if (is_valid_instruction(line) == 0)
            error("Error");
        manage_instruction(&a,&b,line);
    }
    
    while (a.top >= 0)
    {
        printf("%d ", a.tab[a.top]);
        --a.top;
    }

    printf("\n");
    while (b.top >= 0)
    {
        printf("%d ", b.tab[b.top]);
        --b.top;
    }

    if (is_valid_sorted_stack(a, b, ac - 1))
        printf("OK\n");
    else
        printf("KO\n");
    return (0);
}