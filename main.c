#include "push_swap.h"

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
    i = 0;

    while (get_next_line(1, &line))
    {
        if (is_valid_instruction(line) == 0)
            error("Error");
        manage_instruction(a,b,line);
        
    }

    
    if (ac == 2)
    {
        printf("\n%d", a.tab[0]);
        return (0);
    }
    

    while (a.top >= 0)
    {
        printf("%d ", a.tab[a.top]);
        --a.top;
    }
    return (0);
}