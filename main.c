#include "push_swap.h"

int main(int ac, char **av)
{
    int i;
    char *line;
    instruction *instrs;
    instruction *elem;
    instruction *tmp;
    int num_iters;
    int *a;
    int *b;

    i = 1;
    if (ac < 2)
    {
        printf("args empty");
        return (0);
    }
    else
    {
        a = (int *)malloc((ac - 1) * sizeof(int));
        b = (int *)malloc((ac - 1) * sizeof(int));

        while (i < ac)
        {

            is_valid_args(av[i]);
            a[i - 1] = ft_atoi(av[i]);
            is_doubling(a, i - 1);
            i++;
        }
    }
    i = 0;

    instrs = NULL;
    num_iters = 0;
    while (get_next_line(1, &line))
    {
        if (is_valid_instruction(line) == 0)
        {
            printf("Error");
            return (0);
        }

        elem = malloc(sizeof(*elem));
        if (elem == NULL)
            return (0);
        else
        {
            elem->value = malloc(ft_strlen(line));
            if (elem->value == NULL)
                return (0);
            else
            {
                ft_strcpy(elem->value, line);
                elem->suivant = NULL;
                if (instrs == NULL)
                    instrs = elem;
                else
                {
                    tmp = instrs;
                    while (tmp->suivant != NULL)
                        tmp = tmp->suivant;
                    tmp->suivant = elem;
                }
            }
        }
        num_iters++;
        
    }

    
    if (ac == 2)
    {
        printf("\n%d", a[0]);
        return (0);
    }
    if (instrs == NULL)
    {
        printf("empty istrs");
        return (0);
    }
    tmp = instrs;
    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->value, "sa") == 0)
        {
            i = a[0];
            a[0] = a[1];
            a[1] = i;
        }

        printf("%s -> ", tmp->value);
        tmp = tmp->suivant;
    }
    i = 0;
    printf("NULL");
    while (i < ac - 1)
    {
        printf("%d ", a[i]);
        i++;
    }
    return (0);
}