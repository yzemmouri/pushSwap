/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:38:14 by yzemmour          #+#    #+#             */
/*   Updated: 2022/01/14 19:38:16 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_instr	*add_instr(t_instr *instrs, char *oper)
{
	t_instr	*new;
	t_instr	*temp;

	// - error alloctatiom
	if (oper)
	{
		new = malloc(sizeof(t_instr));
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

int	max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

t_instr	*put_elem_top_b(t_env *env, int num, t_instr *instr_b)
{
	int	j;

	if (num >= ((env->b.top) / 2))
	{
		j = env->b.top - num;
		while (j > 0)
		{
			instr_b = add_instr(instr_b, "rb");
			manage_indexed_stack(&env->sdl, &env->a, &env->b, "rb");
			j--;
		}
	}
	else
	{
		j = num + 1;
		while (j > 0)
		{
			instr_b = add_instr(instr_b, "rrb");
			manage_indexed_stack(&env->sdl, &env->a, &env->b, "rrb");
			j--;
		}
	}
	return (instr_b);
}

t_instr	*put_top_b_opt(t_env *env, int n, t_instr *instr_a, t_instr *instr_b)
{
	int		j;
	int		a_instr_len;
	char	*a_instr_type;
	int		rb_len;
	int		rrb_len;

	a_instr_len = 0;
	rb_len = env->b.top - n;
	rrb_len = n + 1;
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
		j = env->b.top - n;
		while (j > 0)
		{
			instr_b = add_instr(instr_b, "rb");
			manage_indexed_stack(&env->sdl, &env->a, &env->b, "rb");
			j--;
		}
	}
	else
	{
		j = n + 1;
		while (j > 0)
		{
			instr_b = add_instr(instr_b, "rrb");
			manage_indexed_stack(&env->sdl, &env->a, &env->b, "rrb");
			j--;
		}
	}
	return (instr_b);
}

t_instr	*put_elem_top_a(t_env *env, int num, t_instr *instr)
{
	int	j;

	if (num >= (int)(env->a.top / 2))
	{
		j = env->a.top - num;
		while (j > 0)
		{
			instr = add_instr(instr, "ra");
			manage_indexed_stack(&env->sdl, &env->a, &env->b, "ra");
			j--;
		}
	}
	else
	{
		j = num + 1;
		while (j > 0)
		{
			instr = add_instr(instr, "rra");
			manage_indexed_stack(&env->sdl, &env->a, &env->b, "rra");
			j--;
		}
	}
	return (instr);
}

int	best_elem(t_indexed_stack *sa, int start, int max)
{
	int	t_top;
	int	t_bottom;
	int	index;
  
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

t_instr	*put_elem_position(t_env *env, int num, t_instr *instr_a, t_instr *instr_b)
{
	int	i;

	i = env->b.top - 1;
	while (i >= 0)
	{
		if (env->b.tab[i].equiv < num && env->b.tab[i + 1].equiv > num)
		{
			instr_b = put_top_b_opt(env, i, instr_a, instr_b);
			break ;
		}
		i--;
	}
	return (instr_b);
}

int	find_max(t_indexed_stack s)
{
	int	i;
	int	max;
	int	index;

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
	int	i;
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

t_instr	*fusion(t_instr *instrs, t_instr *instrs_a, t_instr *instrs_b)
{
	t_instr *tmp1;
	t_instr *tmp2;

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

t_instr	*free_instrs(t_instr *instrs)
{
	t_instr *current;

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

t_instr	*complex_sort(t_env *env, int num_chunk, int total_num)
{
	int				len_chunk;
	int				new_max_min;
	int				max;
	int				index;
	t_instr	*instrs_a;
	t_instr 	*instrs_b;

	len_chunk = total_num / num_chunk;
	max = len_chunk - 1;
	instrs_a = NULL;
	instrs_b = NULL;
	while(env->a.top >= 0)
	{
		index = best_elem(&env->a, max - len_chunk + 1, max);
		if (index != -1)
		{
			instrs_a = put_elem_top_a(env, index, instrs_a);
			if (env->b.top >= 1)
			{
				new_max_min = is_new_min_max(env->b, env->a.tab[env->a.top].equiv);
				if (new_max_min != -1)
					instrs_b = put_top_b_opt(env, new_max_min, instrs_a, instrs_b);
				else
					instrs_b = put_elem_position(env, env->a.tab[env->a.top].equiv, instrs_a, instrs_b);
			}
			env->instrs = fusion(env->instrs, instrs_a, instrs_b);
			instrs_a = free_instrs(instrs_a);
			instrs_b = free_instrs(instrs_b);
			env->instrs = add_instr(env->instrs, "pb");
			manage_indexed_stack(&env->sdl, &env->a, &env->b, "pb");
		}
		else
			max = max + len_chunk;
	}
	env->instrs = put_elem_top_b(env, find_max(env->b), env->instrs);
	
	return (env->instrs);
}

void	print_instrs(t_instr *instrs)
{
	t_instr *current;

	current = instrs;
   	while (current != NULL)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}


t_instr	*three_num(t_env *env, int a, int b, int c)
{
	if (a > b && b < c && c > a)
	{
		env->instrs = add_instr(env->instrs, "sa");
		manage_indexed_stack(&env->sdl, &env->a, &env->b, "sa");
	}
	else if (a > b && b > c && c < a)
	{
		env->instrs = add_instr(env->instrs, "sa");
		env->instrs = add_instr(env->instrs, "rra");
		manage_indexed_stack(&env->sdl, &env->a, &env->b, "sa");
		manage_indexed_stack(&env->sdl, &env->a, &env->b, "rra");
	}
	else if (a > b && b < c && c < a)
	{
		env->instrs = add_instr(env->instrs, "ra");
		manage_indexed_stack(&env->sdl, &env->a, &env->b, "ra");
	}
	else if (a < b && b > c && c > a)
	{
		env->instrs = add_instr(env->instrs, "sa");
		env->instrs = add_instr(env->instrs, "ra");
		manage_indexed_stack(&env->sdl, &env->a, &env->b, "sa");
		manage_indexed_stack(&env->sdl, &env->a, &env->b, "ra");
	}
	else if (a < b && b > c && c < a)
	{
		env->instrs = add_instr(env->instrs, "rra");
		manage_indexed_stack(&env->sdl, &env->a, &env->b, "rra");
	}
	return (env->instrs);
}

char	is_option_activated(char option, int option_index)
{
	return ((option >> option_index) & 1);
}

int	main(int ac, char **av)
{
	int		i;
	t_env	env;

	env.instrs = NULL;
	env.sdl.options = 0;
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
					env.sdl.options |= 1;
				}
				else if (ft_strequ(av[i], "-c"))
				{
					++av;
					--ac;
					--i;
					env.sdl.options |= 2;
				}     
			}
			++i;
		}
		if (ac < 2)
			return (0);
		env.a.tab = (t_indexed_value *)malloc((ac - 1) * sizeof(t_indexed_value));
		env.a.top = -1;
		env.b.tab = (t_indexed_value *)malloc((ac - 1) * sizeof(t_indexed_value));
		env.b.top = -1;
		
		i = ac - 1;
		while (i > 0)
		{
			is_valid_args(av[i]);
			env.a.tab[ac - i - 1].value = ft_atoi(av[i]);
			env.a.tab[ac - i - 1].index = ac - i - 1;
			++env.a.top;
			is_doubling_indexed(env.a);
			--i;
		}
		if (is_option_activated(env.sdl.options, V_OPTION))
			init_sdl(&env.sdl);
		merge_sort(env.a.tab, 0, ac - 2, 1);
		i = 0;
		while (i < ac - 1)
		{
			env.a.tab[i].equiv = i;
			++i;
		}	
		merge_sort(env.a.tab, 0, ac - 2, 0);
		if (is_sorted_indexed_array(env.a.tab, ac - 1))
			return (0);
		else
		{   
			if (ac - 1 == 3)
				env.instrs = three_num(&env, env.a.tab[2].value, env.a.tab[1].value, env.a.tab[0].value);
			else if (ac - 1 <= 10)
				env.instrs = complex_sort(&env, 1, ac - 1);
			else if (ac - 1 <= 100)
				env.instrs = complex_sort(&env, 5, ac - 1);
			else
				env.instrs = complex_sort(&env, 11, ac - 1);
		}
		while (env.b.top > -1)
		{
			env.instrs = add_instr(env.instrs, "pa");
			manage_indexed_stack(&env.sdl, &env.a, &env.b, "pa");
		}
		print_instrs(env.instrs);
		if (is_option_activated(env.sdl.options, V_OPTION))
			loop_program(&env.sdl);
		/*miss free*/
	}
	return (0);
}