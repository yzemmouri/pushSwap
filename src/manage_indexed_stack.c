/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_indexed_stack.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:18:06 by yzemmour          #+#    #+#             */
/*   Updated: 2022/01/14 18:18:09 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	manage_indexed_stack(t_sdl *data,
	t_indexed_stack *sa, t_indexed_stack *sb,
	char *inst)
{
	if (ft_strcmp(inst, "sa") == 0)
		sx_inst_indexed(sa);
	else if (ft_strcmp(inst, "sb") == 0)
		sx_inst_indexed(sb);
	else if (ft_strcmp(inst, "ss") == 0)
		ss_inst_indexed(sa, sb);
	else if (ft_strcmp(inst, "pa") == 0)
		px_inst_indexed(sa, sb);
	else if (ft_strcmp(inst, "pb") == 0)
		px_inst_indexed(sb, sa);
	else if (ft_strcmp(inst, "ra") == 0)
		rot_inst_indexed(sa, 1);
	else if (ft_strcmp(inst, "rb") == 0)
		rot_inst_indexed(sb, 1);
	else if (ft_strcmp(inst, "rr") == 0)
		rot_rot_inst_indexed(sa, sb, 1);
	else if (ft_strcmp(inst, "rra") == 0)
		rot_inst_indexed(sa, 0);
	else if (ft_strcmp(inst, "rrb") == 0)
		rot_inst_indexed(sb, 0);
	else if (ft_strcmp(inst, "rrr") == 0)
		rot_rot_inst_indexed(sa, sb, 0);
	if (data->is_visu)
		draw(data, *sa, *sb);
}

void	print_insts(t_inst *insts)
{
	t_inst	*current;

	current = insts;
	while (current != NULL)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

t_inst	*add_inst(t_inst *insts, char *oper)
{
	t_inst	*new;
	t_inst	*temp;

	new = malloc(sizeof(t_inst));
	if (oper && new)
	{
		new->value = malloc(ft_strlen(oper) + 1);
		if (new->value)
		{
			ft_strcpy(new->value, oper);
			new->next = NULL;
		}
	}
	if (insts == NULL)
		insts = new;
	else
	{
		temp = insts;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (insts);
}

void	op_inst(t_env *env, char *op)
{
	env->insts = add_inst(env->insts, op);
	manage_indexed_stack(&env->sdl, &env->a, &env->b, op);
}

t_inst	*free_insts(t_inst *insts)
{
	t_inst	*current;

	while (insts != NULL)
	{
		current = insts;
		free(current->value);
		free(current);
		insts = insts->next;
	}
	insts = NULL;
	return (insts);
}
