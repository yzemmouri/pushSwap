/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 21:40:48 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/18 00:53:26 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_print(int i, int p, int c, char *str)
{
	while (--i >= 0)
	{
		str[i] = (p % 10) + '0';
		p /= 10;
	}
	if (c < 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	t_vals	v;
	int		c;
	char	*str;

	v.a = 1;
	c = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		v.a++;
		n = -n;
	}
	v.b = n;
	while (n >= 10)
	{
		n = n / 10;
		v.a++;
	}
	str = (char *)malloc((v.a + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[v.a] = '\0';
	ft_print(v.a, v.b, c, str);
	return (str);
}
