#include "push_swap.h"


void manage_instruction(t_stack sa, t_stack sb, char *instr)
{
    if (ft_strcmp(instr, "sa") == 0)
    {
        if (sa.top < 1)
            error("Error");
        ft_swap(sa.tab + sa.top, sa.tab + sa.top - 1);
    }
    else if (ft_strcmp(instr, "sb") == 0)
    {
         if (sb.top < 1)
            error("Error");
        ft_swap(sb.tab + sb.top, sb.tab + sb.top - 1);
    }
}