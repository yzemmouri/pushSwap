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
        else if (ac - 1 <= 5)
        {
            if (ac - 1 == 5)
            {
                manage_instruction_indexed_stack(&a, &b, "pb");
                printf("pb\n");
            }
            manage_instruction_indexed_stack(&a, &b, "pb");
            printf("pb\n");
            three_num(a.tab[2].value, a.tab[1].value, a.tab[0].value, &a, &b);

            manage_instruction_indexed_stack(&a, &b, "pa");
            printf("pa\n");

            if (a.tab[a.top].value > a.tab[0].value)
            {
                manage_instruction_indexed_stack(&a, &b, "ra");
                printf("ra\n");
            }
            else if (a.tab[a.top].value > a.tab[1].value && a.tab[a.top].value < a.tab[0].value)
            {
                manage_instruction_indexed_stack(&a, &b, "rra");
                printf("rra\n");
                manage_instruction_indexed_stack(&a, &b, "pb");
                printf("pb\n");
                three_num(a.tab[2].value, a.tab[1].value, a.tab[0].value, &a, &b);
                manage_instruction_indexed_stack(&a, &b, "pa");
                printf("pa\n");
                manage_instruction_indexed_stack(&a, &b, "ra");
                printf("ra\n");
            }
            else if (a.tab[a.top].value > a.tab[2].value && a.tab[a.top].value < a.tab[1].value)
            {    
                manage_instruction_indexed_stack(&a, &b, "sa");
                printf("sa\n");
            }
            if (ac - 1 == 5)
            {
                manage_instruction_indexed_stack(&a, &b, "pa");
                printf("pa\n");
                if (a.tab[a.top].value > a.tab[0].value)
                {
                    manage_instruction_indexed_stack(&a, &b, "ra");
                    printf("ra\n");
                }
                else if (a.tab[a.top].value > a.tab[1].value && a.tab[a.top].value < a.tab[0].value)
                {

                }
            }
            
        }


        else if (ac - 1 <= 100)
        {
            int i;
            int len_chunk = 2;

            int min = 0;
            int max = (a.top / 5);

            int up = a.top;
            int down = 0;

            int chunk_num = 1;

            int middle = a.top / 2;

            while (down <= middle)
            {
                if (a.tab[down].value >= min && a.tab[down].value <= max)
                {
                    printf("**%d**",down);
                    break;
                }
                down++;
            }
            while (up > middle)
            {
                if (a.tab[up].value >= min && a.tab[up].value <= max)
                {
                    printf("++%d++",up);
                    break;
                }
                up--;
            }
            if (down + 1 < a.top - up)
            {
                printf("kkk");
                i = down + 1;
                while (i > 0)
                {
                    manage_instruction_indexed_stack(&a, &b, "rra");
                    i--;
                }
            }
            else
            {
                i = a.top - up;
                while (i > 0)
                {
                    printf("fef");
                    manage_instruction_indexed_stack(&a, &b, "ra");
                    i--;
                }
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