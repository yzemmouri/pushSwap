#include "push_swap.h"

void    rotab(int *tab, int top, int to_up)
{
    int i;
    int tmp;
    int limit;
    
    i = to_up ? top : 0;
    tmp = tab[to_up ? top : 0];
    limit = to_up ? 0 : top;
    if(to_up)
        while (i > limit)
        {
            tab[i] = tab[i - 1];
            --i;
        }
    else
        while (i < limit)
        {
            tab[i] = tab[i + 1];
            ++i;
        }
    tab[i] = tmp;
}

void    push_stack(t_stack *s1, t_stack *s2)
{
    s1->top = ++s1->top;
    s1->tab[s1->top] = s2->tab[s2->top];
    s2->top = --s2->top;
}

void    manage_instruction(t_stack *sa, t_stack *sb, char *instr)
{
    if (ft_strcmp(instr, "sa") == 0)
    {
        if (sa->top > 0)
            ft_swap(sa->tab + sa->top, sa->tab + sa->top - 1);
    }
    else if (ft_strcmp(instr, "sb") == 0)
    {
         if (sb->top > 0)
            ft_swap(sb->tab + sb->top, sb->tab + sb->top - 1);
    }
    else if (ft_strcmp(instr, "ss") == 0)
    {
        if (sa->top > 0)    
            ft_swap(sa->tab + sa->top, sa->tab + sa->top - 1);
        if (sb->top > 0)
            ft_swap(sb->tab + sb->top, sb->tab + sb->top - 1);
    }
    else if (ft_strcmp(instr, "pa") == 0)
    {
        if (sb->top >= 0)
            push_stack(sa, sb);
    }
    else if (ft_strcmp(instr, "pb") == 0)
    {
        if (sa->top >= 0)
            push_stack(sb, sa);
    }
    else if (ft_strcmp(instr, "ra") == 0)
    {
        if (sa->top > 0)
            rotab(sa->tab, sa->top, 1);
    }
    else if (ft_strcmp(instr, "rb") == 0)
    {
        if (sb->top > 0)
            rotab(sb->tab, sb->top, 1);
    }
    else if (ft_strcmp(instr, "rr") == 0)
    {
        if (sa->top > 0)
            rotab(sa->tab, sa->top, 1);
        if (sb->top > 0)
            rotab(sb->tab, sb->top, 1);
    }
    else if (ft_strcmp(instr, "rra") == 0)
    {
        if (sa->top > 0)
            rotab(sa->tab, sa->top, 0);
    }
    else if (ft_strcmp(instr, "rrb") == 0)
    {
        if (sb->top > 0)
            rotab(sb->tab, sb->top, 0);
    }
    else if (ft_strcmp(instr, "rrr") == 0)
    {
        if (sa->top > 0)
            rotab(sa->tab, sa->top, 0);
        if (sb->top > 0)
            rotab(sb->tab, sb->top, 0);
    }
}