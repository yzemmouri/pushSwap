/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:54:19 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/18 05:56:18 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (j == 1 && *s == c)
			j = 0;
		if (j == 0 && *s != c)
		{
			j = 1;
			i++;
		}
		s++;
	}
	return (i);
}

char	**ft_strsplit(char const *s, char c)
{
	int		word;
	t_vals	v;
	int		start;
	char	**tab;

	if (s == 0 || c == 0)
		return (NULL);
	word = ft_count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (!tab)
		return (NULL);
	v.a = 0;
	v.b = -1;
	while (++v.b < word)
	{
		while (s[v.a] && s[v.a] == c)
			v.a++;
		start = v.a;
		while (s[v.a] && s[v.a] != c)
			v.a++;
		tab[v.b] = ft_strsub(s, start, v.a - start);
		v.a++;
	}
	tab[v.b] = NULL;
	return (tab);
}
