/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:45:46 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/16 00:58:27 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *elem1, int *elem2)
{
	int	tmp;

	tmp = *elem1;
	*elem1 = *elem2;
	*elem2 = tmp;
}
