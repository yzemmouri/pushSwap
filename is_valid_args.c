#include "push_swap.h"


void is_valid_args(char *arg)
{
    int i;

    i = 0;
    if (arg[i] == '-')
        i++;
    while (arg[i] != '\0')
    {
        if (ft_isdigit(arg[i]) == 0)
            error("Error");
        is_int_range(arg, "-2147483648", "2147483647");
        i++;
    }
}

void is_doubling(t_stack s)
{
    int i;

    i = 0;
    while (i < s.top)
    {
        if (s.tab[i] == s.tab[s.top])
        error("Error");
        i++;
    }
}

int is_valid_instruction(char *instr)
{
    if (ft_strcmp(instr, "sa") && ft_strcmp(instr, "sb") && ft_strcmp(instr, "ss") && ft_strcmp(instr, "pa") && ft_strcmp(instr, "pb") && ft_strcmp(instr, "ra") && ft_strcmp(instr, "rb") && ft_strcmp(instr, "rr") && ft_strcmp(instr, "rra") && ft_strcmp(instr, "rrb") && ft_strcmp(instr, "rrr"))
        return (0);
    return (1);
}