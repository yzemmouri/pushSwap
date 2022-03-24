/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 02:38:10 by yzemmour          #+#    #+#             */
/*   Updated: 2022/03/24 02:38:17 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sdl_error(char *message)
{
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();
	exit(-1);
}

int	convert_range(int n, t_range old, t_range new)
{
	return ((((n - old.min) * (new.max - new.min))
			/ (old.max - old.min)) + new.min);
}

void	event_listner(void)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event))
	{
		if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			|| event.type == SDL_QUIT)
		{
			exit(1);
		}
	}
}

uint32_t	rgb(double ratio)
{
	int		normalized;
	int		region;
	int		x;
	t_color	c;

	normalized = (int)(ratio * 256 * 4);
	region = normalized / 256;
	x = normalized % 256;
	c.r = 0;
	c.g = 0;
	c.b = 0;
	if (region == 0)
		c = (t_color){255, x, 0};
	if (region == 1)
		c = (t_color){255 - x, 255, 0};
	if (region == 2)
		c = (t_color){0, 255, x};
	if (region == 3)
		c = (t_color){0, 255 - x, 255};
	return (c.r | (c.g << 8) | (c.b << 16));
}
