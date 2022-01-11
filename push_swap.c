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

int is_new_max(t_indexed_stack s, int num)
{
	int i;

	i = s.top;
	while (i >= 0)
	{
		if (s.tab[i].value > num)
			return (1);
		i--;
	}
	return (0);
}

int elem_position(t_indexed_stack s, int num)
{
	int i;

	i = s.top;
	while (i >= 0)
	{
		if (s.tab[i].value > num && s.tab[i].value > num)
			return (1);
		i--;
	}
	return (0);
}

int is_new_min(t_indexed_stack s, int num)
{
	int i;
	int max;
	int index;
	int is_min;

	is_min = 1;
	max = -1;
	index = -1;
	i = s.top;
	while (i >= 0)
	{
		if (s.tab[i].value < num)
			is_min = 0;
		if (s.tab[i].value > max)
		{
			max = s.tab[i].value;
			index = s.tab[i].index;
		}
		i--;
	}
	if (is_min)
		return index;
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
    printf("\n\n");
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
    while (i < ac - 1)
    {
        printf("%d-->%d\n", a.tab[i].index, a.tab[i].value);
        ++i;
    }
    
    if (is_sorted_indexed_array(a.tab, ac - 1))
        return (0);
    else
    {   
        if (ac - 1 == 3)
            three_num(a.tab[2].value, a.tab[1].value, a.tab[0].value, &a, &b);
        else if (ac - 1 <= 10)
        {
			int i = a.top;
            int num_chunk = 1;
			int new_max;
			int new_min;
			while(i >= 0)
			{
				if (b.top < 1)
				{
					printf("pb");
					manage_instruction_indexed_stack(&a, &b, "pb");
				}
				else
				{
					new_max = is_new_max(b, a.tab[i].value);
					if (new_max)
					{
						printf("pb");
						manage_instruction_indexed_stack(&a, &b, "pb");
					}
					else if ((new_min = is_new_min(b, a.tab[i].value)) != -1)
					{
						if (new_min >= b.top / 2)
						{
							int j = b.top - new_min;
							while (j > 0)
							{
								printf("rb");
								manage_instruction_indexed_stack(&a, &b, "rb");
								j--;
							}
						}
						else
						{
							int j = new_min + 1;
							while (j > 0)
							{
								printf("rrb");
								manage_instruction_indexed_stack(&a, &b, "rrb");
								j--;
							}
						}
						printf("pb");
						manage_instruction_indexed_stack(&a, &b, "pb");
					}
					else
					{

					}
				}
				
				i--;
			}
            
        }
        // else if (ac - 1 <= 500)
        // {
            
        // }
    }
    // while (a.top >= 0)
    // {
    //     printf("%d ", a.tab[a.top].value);
    //     --a.top;
    // }

    printf("\n");
    while (b.top >= 0)
    {
        printf("%d ", b.tab[b.top].value);
        --b.top;
    }
    return (0);
}