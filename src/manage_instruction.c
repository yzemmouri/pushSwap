#include "../push_swap.h"

void    sx_instr(t_stack *s)
{
    if (s->top > 0)
        ft_swap(s->tab + s->top, s->tab + s->top - 1);
}

void    ss_instr(t_stack *s1, t_stack *s2)
{
    sx_instr(s1);
    sx_instr(s2);
}

void    px_instr(t_stack *s1, t_stack *s2)
{
    if (s2->top >= 0)
    {
        s1->top = ++s1->top;
        s1->tab[s1->top] = s2->tab[s2->top];
        s2->top = --s2->top;
    }
}

void    rot_instr(int *tab, int top, int to_up)
{
    if (top > 0)
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
}

void    rot_rot_instr(int *tab1, int *tab2, int top1, int top2, int to_up)
{
    rot_instr(tab1, top1, to_up);
    rot_instr(tab2, top2, to_up);
}

void    manage_instruction(t_stack *sa, t_stack *sb, char *instr)
{
    if (ft_strcmp(instr, "sa") == 0)
        sx_instr(sa);
    else if (ft_strcmp(instr, "sb") == 0)
         sx_instr(sb);
    else if (ft_strcmp(instr, "ss") == 0)
        ss_instr(sa,sb);
    else if (ft_strcmp(instr, "pa") == 0)
        px_instr(sa, sb);
    else if (ft_strcmp(instr, "pb") == 0)
        px_instr(sb, sa);
    else if (ft_strcmp(instr, "ra") == 0)
        rot_instr(sa->tab, sa->top, 1);
    else if (ft_strcmp(instr, "rb") == 0)
        rot_instr(sb->tab, sb->top, 1);
    else if (ft_strcmp(instr, "rr") == 0)
        rot_rot_instr(sa->tab, sb->tab, sa->top, sb->top, 1);
    else if (ft_strcmp(instr, "rra") == 0)
        rot_instr(sa->tab, sa->top, 0);
    else if (ft_strcmp(instr, "rrb") == 0)
        rot_instr(sb->tab, sb->top, 0);
    else if (ft_strcmp(instr, "rrr") == 0)
        rot_rot_instr(sa->tab, sb->tab, sa->top, sb->top, 0);
}