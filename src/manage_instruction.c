/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_instuction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:17:37 by yzemmour          #+#    #+#             */
/*   Updated: 2022/01/14 19:17:40 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	manage_instuction(t_stack *sa, t_stack *sb, char *inst)
{
	if (ft_strcmp(inst, "sa") == 0)
		sx_inst(sa);
	else if (ft_strcmp(inst, "sb") == 0)
		sx_inst(sb);
	else if (ft_strcmp(inst, "ss") == 0)
		ss_inst(sa, sb);
	else if (ft_strcmp(inst, "pa") == 0)
		px_inst(sa, sb);
	else if (ft_strcmp(inst, "pb") == 0)
		px_inst(sb, sa);
	else if (ft_strcmp(inst, "ra") == 0)
		rot_inst(sa, 1);
	else if (ft_strcmp(inst, "rb") == 0)
		rot_inst(sb, 1);
	else if (ft_strcmp(inst, "rr") == 0)
		rot_rot_inst(sa, sb, 1);
	else if (ft_strcmp(inst, "rra") == 0)
		rot_inst(sa, 0);
	else if (ft_strcmp(inst, "rrb") == 0)
		rot_inst(sb, 0);
	else if (ft_strcmp(inst, "rrr") == 0)
		rot_rot_inst(sa, sb, 0);
}
