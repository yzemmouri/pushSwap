#include "push_swap.h"

void    three_num(int a, int b, int c, t_indexed_stack *sa, t_indexed_stack *sb)
{
    if (a > b && b < c && c > a)
    {
        printf("sa\n");
        manage_instruction_indexed_stack(sa, sb, "sa");
    }
    else if (a > b && b > c && c < a)
    {
        printf("sa\nrra\n");
        manage_instruction_indexed_stack(sa, sb, "sa");
        manage_instruction_indexed_stack(sa, sb, "rra");
    }
    else if (a > b && b < c && c < a)
    {
        printf("ra\n");
        manage_instruction_indexed_stack(sa, sb, "ra");
    }
    else if (a < b && b > c && c > a)
    {
        printf("sa\nra\n");
        manage_instruction_indexed_stack(sa, sb, "sa");
        manage_instruction_indexed_stack(sa, sb, "ra");
    }
    else if (a < b && b > c && c < a)
    {
        printf("rra\n");
        manage_instruction_indexed_stack(sa, sb, "rra");
    }
}

void put_elem_top_b(t_indexed_stack *sa, t_indexed_stack *sb, int num)
{
    int j;

    if (num >= (int)(sb->top / 2))
	{
		j = sb->top - num;
		while (j > 0)
		{
			printf("rb\n");
			manage_instruction_indexed_stack(sa, sb, "rb");
			j--;
		}
	}
	else
	{
		j = num + 1;
		while (j > 0)
		{
			printf("rrb\n");
			manage_instruction_indexed_stack(sa, sb, "rrb");
			j--;
		}
	}
}

void put_elem_top_a(t_indexed_stack *sa, t_indexed_stack *sb, int num)
{
    int j;

    if (num >= (int)(sa->top / 2))
	{
		j = sa->top - num;
		while (j > 0)
		{
			printf("ra\n");
			manage_instruction_indexed_stack(sa, sb, "ra");
			j--;
		}
	}
	else
	{
		j = num + 1;
		while (j > 0)
		{
			printf("rra\n");
			manage_instruction_indexed_stack(sa, sb, "rra");
			j--;
		}
	}
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
        if (sa->tab[t_bottom].value >= start && sa->tab[t_bottom].value <= max)
        {
            index = t_bottom;
            break ;
        }
        if (sa->tab[t_top].value >= start && sa->tab[t_top].value <= max)
        {
            index = t_top;
            break ;
        }
        t_top--;
        t_bottom++;
    }
    return (index);   
}


void put_elem_position(t_indexed_stack *sa, t_indexed_stack *sb, int num)
{
	int i;

	i = sb->top - 1;
	while (i >= 0)
	{
		if (sb->tab[i].value < num && sb->tab[i + 1].value > num)
        {
            put_elem_top_b(sa, sb, i);
            break ;
        }
		i--;
	}
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
        if (s.tab[i].value > num)
			is_max = 0;
		if (s.tab[i].value < num)
			is_min = 0;
		if (s.tab[i].value > max)
		{
			max = s.tab[i].value;
			index = i;
		}
		i--;
	}
	if (is_min || is_max)
		return (index);
	return (-1);
}

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
    // while (i < ac - 1)
    // {
    //     printf("%d-->%d\n", a.tab[i].index, a.tab[i].value);
    //     ++i;
    // }
    // printf("\n\n");
    // printf("--%d--",a.tab[0].value);
    mergeSort(a.tab, 0, ac - 2, 1);
    // i=0;
    // while (i < ac - 1)
    // {
    //     printf("%d-->%d\n", a.tab[i].index, a.tab[i].value);
    //     ++i;
    // }
    // i = 0;
    // printf("\n\n");
    while (i < ac - 1)
    {
        a.tab[i].value = i;
        ++i;
    }
     i = 0;
    // while (i < ac - 1)
    // {
    //     printf("%d-->%d\n", a.tab[i].index, a.tab[i].value);
    //     ++i;
    // }
    // printf("\n\n");
    mergeSort(a.tab, 0, ac - 2, 0);

    i = 0;
    // while (i < ac - 1)
    // {
    //     printf("%d-->%d\n", a.tab[i].index, a.tab[i].value);
    //     ++i;
    // }
    
    if (is_sorted_indexed_array(a.tab, ac - 1))
        return (0);
    else
    {   
        if (ac - 1 == 3)
            three_num(a.tab[2].value, a.tab[1].value, a.tab[0].value, &a, &b);
        else if (ac - 1 <= 10)
        {
			int i = a.top;
            // int num_chunk = 1;
			int new_max_min;
			// int new_min;
			while(i >= 0)
			{
				if (b.top >= 1)
				{
					new_max_min = is_new_min_max(b, a.tab[i].value);
					if (new_max_min != -1)
					    put_elem_top_b(&a, &b, new_max_min);
					else
                        put_elem_position(&a, &b, a.tab[i].value);
				}
                printf("pb\n");
                manage_instruction_indexed_stack(&a, &b, "pb");
				i--;
                // int j = b.top;
                // printf("[");
                // while (j >= 0)
                // {
                //     printf("%d ", b.tab[j].value);
                //     j--;
                // }
                // printf("]");
			}
            
        }
        else if (ac - 1 <= 100)
        {
            int num_chunk = 5;
            int len_chunk = (ac - 1) / num_chunk;
			int new_max_min;
			int max;
            int index;

            max = len_chunk - 1;
			while(num_chunk > 0)
			{
                index = best_elem(&a, max - len_chunk + 1, max);
                while (index != -1)
                {
                    put_elem_top_a(&a, &b, index);
				    if (b.top >= 1)
				    {
				    	new_max_min = is_new_min_max(b, a.tab[a.top].value);
				    	if (new_max_min != -1)
				    	    put_elem_top_b(&a, &b, new_max_min);
				    	else
                            put_elem_position(&a, &b, a.tab[a.top].value);
				    }
                    printf("pb\n");
                    manage_instruction_indexed_stack(&a, &b, "pb");
                    index = best_elem(&a, max - len_chunk + 1, max);
                }
                max = max + len_chunk;
				num_chunk--;
			}
        }
    }
    while (a.top >= 0)
    {
        printf("%d ", a.tab[a.top].value);
        --a.top;
    }
    printf("\n");
    while (b.top >= 0)
    {
        printf("%d ", b.tab[b.top].value);
        --b.top;
    }
    return (0);
}