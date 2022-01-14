#include "../push_swap.h"

t_instruction   *add_instr(t_instruction *instrs, char *oper)
{
    t_instruction *new;
    t_instruction *temp;

    /* - error alloctatiom*/
    if (oper)
    {
        new = malloc(sizeof(t_instruction));
        if (new)
        {
            new->value = malloc(ft_strlen(oper) + 1);
            if (new->value)
            {
                ft_strcpy(new->value, oper);
                new->next = NULL;
            }
        }
    }
    if (instrs == NULL)
        instrs = new;
    else
    {
        temp = instrs;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
    return (instrs);
}

int max(int a, int b)
{
    if (a >= b)
        return (a);
    return (b);
}

t_instruction  *put_elem_top_b(t_sdl *data, t_indexed_stack *sa,t_indexed_stack *sb, int num, t_instruction *instr_b)
{
    int j;

    if (num >= ((sb->top) / 2))
	{
        j = sb->top - num;
		while (j > 0)
		{
            instr_b = add_instr(instr_b, "rb");
			manage_instruction_indexed_stack(data, sa, sb, "rb");
			j--;
		}
	}
	else
	{
        j = num + 1;
		while (j > 0)
		{
            instr_b = add_instr(instr_b, "rrb");
			manage_instruction_indexed_stack(data, sa, sb, "rrb");
			j--;
		}
	}
    return (instr_b);
}

t_instruction  *put_elem_top_b_opt(t_sdl *data, t_indexed_stack *sa, t_indexed_stack *sb, int num, t_instruction *instr_a, t_instruction *instr_b)
{
    int     j;
    int     a_instr_len;
    char    *a_instr_type;
    int     rb_len;
    int     rrb_len;

    a_instr_len = 0;
    rb_len = sb->top - num;
    rrb_len = num + 1;
    if (instr_a)
    {
        a_instr_type = instr_a->value;
        while (instr_a)
        {
            ++a_instr_len;
            instr_a = instr_a->next;
        }
        if (ft_strcmp(a_instr_type, "ra") == 0)
        {
            rb_len = max(a_instr_len + 1, rb_len);
            rrb_len = a_instr_len + 1 + rrb_len;
        }
        else
        {
            rrb_len = max(a_instr_len + 1, rrb_len);
            rb_len = a_instr_len + 1 + rb_len;
        }
    }
    if (rb_len <= rrb_len)
	{
        j = sb->top - num;
		while (j > 0)
		{
            instr_b = add_instr(instr_b, "rb");
			manage_instruction_indexed_stack(data, sa, sb, "rb");
			j--;
		}
	}
	else
	{
        j = num + 1;
		while (j > 0)
		{
            instr_b = add_instr(instr_b, "rrb");
			manage_instruction_indexed_stack(data, sa, sb, "rrb");
			j--;
		}
	}
    return (instr_b);
}

t_instruction *put_elem_top_a(t_sdl *data, t_indexed_stack *sa, t_indexed_stack *sb, int num, t_instruction *instr)
{
    int j;

    if (num >= (int)(sa->top / 2))
	{
		j = sa->top - num;
		while (j > 0)
		{
            instr = add_instr(instr, "ra");
			manage_instruction_indexed_stack(data, sa, sb, "ra");
			j--;
		}
	}
	else
	{
		j = num + 1;
		while (j > 0)
		{
            instr = add_instr(instr, "rra");
			manage_instruction_indexed_stack(data, sa, sb, "rra");
			j--;
		}
	}
    return (instr);
}

int best_elem(t_indexed_stack *sa, int start, int max)
{
    int t_top;
    int t_bottom;
    int index;
  
    t_top = sa->top;
    t_bottom = 0;
    index = -1;
    while (t_top >= t_bottom)
    {
        if (sa->tab[t_bottom].equiv >= start && sa->tab[t_bottom].equiv <= max)
        {
            index = t_bottom;
            break ;
        }
        if (sa->tab[t_top].equiv >= start && sa->tab[t_top].equiv <= max)
        {
            index = t_top;
            break ;
        }
        t_top--;
        t_bottom++;
    }
    return (index);   
}


t_instruction *put_elem_position(t_sdl *data, t_indexed_stack *sa, t_indexed_stack *sb, int num, t_instruction *instr_a, t_instruction *instr_b)
{
	int i;

	i = sb->top - 1;
	while (i >= 0)
	{
		if (sb->tab[i].equiv < num && sb->tab[i + 1].equiv > num)
        {
            instr_b = put_elem_top_b_opt(data, sa, sb, i, instr_a, instr_b);
            break ;
        }
		i--;
	}
    return (instr_b);
}

int find_max(t_indexed_stack s)
{
	int i;
	int max;
    int index;

	max = s.tab[s.top].equiv;
    index = s.top;
	i = s.top - 1;
	while (i >= 0)
	{
		if (s.tab[i].equiv > max)
		{
			max = s.tab[i].equiv;
            index = i;
		}
		i--;
	}
	return (index);
}

int is_new_min_max(t_indexed_stack s, int num)
{
	int i;
	int max;
	int index;
	int is_min;
    int is_max;

	is_min = 1;
    is_max = 1;
	max = -1;
	index = -1;
	i = s.top;
	while (i >= 0)
	{
        if (s.tab[i].equiv > num)
			is_max = 0;
		if (s.tab[i].equiv < num)
			is_min = 0;
		if (s.tab[i].equiv > max)
		{
			max = s.tab[i].equiv;
			index = i;
		}
		i--;
	}
	if (is_min || is_max)
		return (index);
	return (-1);
}

t_instruction *fusion(t_instruction *instrs, t_instruction *instrs_a, t_instruction *instrs_b)
{
    t_instruction *tmp1;
    t_instruction *tmp2;

    tmp1 = instrs_a;
    tmp2 = instrs_b;
    while (tmp1 && tmp2)
    {
        if (ft_strcmp(tmp1->value, "ra") == 0 && ft_strcmp(tmp2->value, "rb") == 0)
            instrs = add_instr(instrs, "rr");
        else if (ft_strcmp(tmp1->value, "rra") == 0 && ft_strcmp(tmp2->value, "rrb") == 0)
            instrs = add_instr(instrs, "rrr");
        else
        {
            instrs = add_instr(instrs, tmp2->value);
            instrs = add_instr(instrs, tmp1->value);
        }
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }

    while (tmp2)
    {
        instrs = add_instr(instrs, tmp2->value);
        tmp2 = tmp2->next;
    }
    while (tmp1)
    {
        instrs = add_instr(instrs, tmp1->value);
        tmp1 = tmp1->next;
    }
    return (instrs);
}



t_instruction    *free_instrs(t_instruction   *instrs)
{
    t_instruction *current;

    while (instrs != NULL)
    {
        current = instrs;
        free(current->value);
        free(current);
        instrs = instrs->next;
    }
    instrs = NULL;
    return (instrs);
}

t_instruction    *complex_sort(t_sdl *data, t_indexed_stack *sa, t_indexed_stack *sb, int num_chunk, int total_num, t_instruction *instrs)
{
    int len_chunk = total_num / num_chunk;
	int new_max_min;
	int max;
    int index;
    t_instruction   *instrs_a;
    t_instruction   *instrs_b;

    max = len_chunk - 1;
    instrs_a = NULL;
    instrs_b = NULL;
	while(sa->top >= 0)
	{
        index = best_elem(sa, max - len_chunk + 1, max);
        if (index != -1)
        {
            instrs_a = put_elem_top_a(data, sa, sb, index, instrs_a);
		    if (sb->top >= 1)
		    {
		    	new_max_min = is_new_min_max(*sb, sa->tab[sa->top].equiv);
		    	if (new_max_min != -1)
		    	    instrs_b = put_elem_top_b_opt(data, sa, sb, new_max_min, instrs_a, instrs_b);
		    	else
                    instrs_b = put_elem_position(data, sa, sb, sa->tab[sa->top].equiv, instrs_a,instrs_b);
		    }
            instrs = fusion(instrs, instrs_a, instrs_b);

            instrs_a = free_instrs(instrs_a);
            instrs_b = free_instrs(instrs_b);
            instrs = add_instr(instrs, "pb");
            manage_instruction_indexed_stack(data, sa, sb, "pb");
        }
        else
            max = max + len_chunk;
	}
    instrs = put_elem_top_b(data, sa, sb, find_max(*sb), instrs);
    
    return (instrs);
}


void    print_instrs(t_instruction *instrs)
{
    t_instruction *current;

    current = instrs;
   	while (current != NULL)
    {
        printf("%s\n", current->value);
        current = current->next;
    }
}


t_instruction   *three_num(t_sdl *data, int a, int b, int c, t_indexed_stack *sa,t_indexed_stack *sb, t_instruction *instrs)
{
    if (a > b && b < c && c > a)
    {
        instrs = add_instr(instrs, "sa");
        manage_instruction_indexed_stack(data, sa, sb, "sa");
    }
    else if (a > b && b > c && c < a)
    {
        instrs = add_instr(instrs, "sa");
        instrs = add_instr(instrs, "rra");
        manage_instruction_indexed_stack(data, sa, sb, "sa");
        manage_instruction_indexed_stack(data, sa, sb, "rra");
    }
    else if (a > b && b < c && c < a)
    {
        instrs = add_instr(instrs, "ra");
        manage_instruction_indexed_stack(data, sa, sb, "ra");
    }
    else if (a < b && b > c && c > a)
    {
        instrs = add_instr(instrs, "sa");
        instrs = add_instr(instrs, "ra");
        manage_instruction_indexed_stack(data, sa, sb, "sa");
        manage_instruction_indexed_stack(data, sa, sb, "ra");
    }
    else if (a < b && b > c && c < a)
    {
        instrs = add_instr(instrs, "rra");
        manage_instruction_indexed_stack(data, sa, sb, "rra");
    }
    return (instrs);
}

char        is_option_activated(char option, int option_index)
{
    return ((option >> option_index) & 1);
}

int main(int ac, char **av)
{
    int i;
    t_indexed_stack a;
    t_indexed_stack b;
    t_instruction   *instrs;

    t_sdl sdl_tools;

    instrs = NULL;
    sdl_tools.options = 0;
    if (ac < 2)
        return (0);
    else
    {
        i = 1;
        while (i <= 2)
        {
            if (av[i][0] == '-')
            {
                if (ft_strequ(av[i], "-v"))
                {
                    ++av;
                    --ac;
                    --i;
                    sdl_tools.options |= 1;
                }
                else if (ft_strequ(av[i], "-c"))
                {
                    ++av;
                    --ac;
                    --i;
                    sdl_tools.options |= 2;
                }     
            }
            ++i;
        }
        if (ac < 2)
            return (0);
        a.tab = (t_indexed_value *)malloc((ac - 1) * sizeof(t_indexed_value));
        a.top = -1;
        b.tab = (t_indexed_value *)malloc((ac - 1) * sizeof(t_indexed_value));
        b.top = -1;
        
        i = ac - 1;
        while (i > 0)
        {
            is_valid_args(av[i]);
            a.tab[ac - i - 1].value = ft_atoi(av[i]);
            a.tab[ac - i - 1].index = ac - i - 1;
            ++a.top;
            is_doubling_indexed(a);
            --i;
        }
    if (is_option_activated(sdl_tools.options, V_OPTION))
        init_sdl(&sdl_tools);
    mergeSort(a.tab, 0, ac - 2, 1);
    
    i = 0;
    while (i < ac - 1)
    {
        a.tab[i].equiv = i;
        ++i;
    }
    
    mergeSort(a.tab, 0, ac - 2, 0);

    
    if (is_sorted_indexed_array(a.tab, ac - 1))
        return (0);
    else
    {   
        if (ac - 1 == 3)
            instrs = three_num(&sdl_tools, a.tab[2].value, a.tab[1].value, a.tab[0].value, &a, &b, instrs);
        else if (ac - 1 <= 10)
            instrs = complex_sort(&sdl_tools, &a, &b, 1, ac - 1, instrs);
        else if (ac - 1 <= 100)
            instrs = complex_sort(&sdl_tools, &a, &b, 5, ac - 1, instrs);
        else
            instrs = complex_sort(&sdl_tools, &a, &b, 11, ac - 1, instrs);
    }
    
    while (b.top > -1)
    {
        instrs = add_instr(instrs, "pa");
        manage_instruction_indexed_stack(&sdl_tools,&a, &b, "pa");
    }

    print_instrs(instrs);

    while (a.top >= 0)
    {
        printf("%d ", a.tab[a.top].value);
        --a.top;
        
    }

    printf("\n-------------------- --------\n");

    while (b.top >= 0)
    {
       printf("%d --", b.tab[b.top].value);
        --b.top;
    }
    // sleep(2);
    // printf("loooop\n");
    // SDL_Delay(2000);
    if (is_option_activated(sdl_tools.options, V_OPTION))
        loop_program(&sdl_tools);
    /*miss free*/
    }

    return (0);
}