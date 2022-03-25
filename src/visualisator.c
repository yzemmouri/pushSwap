/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 00:57:39 by yzemmour          #+#    #+#             */
/*   Updated: 2022/01/17 00:57:41 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	init_sdl(t_sdl *data)
{
	data->win = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		sdl_error("initialisation SDL");
	data->win = SDL_CreateWindow("PUSH SWAP :)", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!data->win)
		sdl_error("Creation window");
	data->rend = SDL_CreateRenderer(data->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!data->rend)
		sdl_error("Creation render");
	if (SDL_SetRenderDrawColor(data->rend, 0, 0, 0, 255) != 0)
		sdl_error("Get color failed");
	if (TTF_Init() != 0)
		sdl_error("Font init error");
	data->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 58);
	if (data->font == NULL)
		sdl_error("Font error");
	SDL_PumpEvents();
}

void	write_text(t_sdl *data, char *str, int x)
{
	SDL_Color		white;
	SDL_Surface		*surface_message;
	SDL_Texture		*message;
	SDL_Rect		message_rect;

	white = (SDL_Color){255, 255, 255, 255};
	if (data->vis_col)
		white = (SDL_Color){255, 0, 255, 255};
	surface_message = TTF_RenderText_Blended(data->font, str, white);
	message = SDL_CreateTextureFromSurface(data->rend, surface_message);
	message_rect.x = x;
	message_rect.y = 20;
	message_rect.w = surface_message->w;
	message_rect.h = surface_message->h;
	SDL_RenderCopy(data->rend, message, NULL, &message_rect);
	SDL_FreeSurface(surface_message);
	SDL_DestroyTexture(message);
}

void	visualisator(t_sdl *data, t_indexed_stack s, int x, int height)
{
	int			j;
	int			color;
	int			h;
	SDL_Rect	rec;

	j = -1;
	if (s.top >= 0)
	{
		h = STACK_H / height;
		while (++j <= s.top)
		{
			if (data->vis_col)
			{
				color = rgb((double)(s.tab[j].equiv) / height);
				SDL_SetRenderDrawColor(data->rend,
					color & 0x0000FF, (color & 0x00FF00) >> 8,
					(color & 0xFF0000) >> 16, 255);
			}
			else
				SDL_SetRenderDrawColor(data->rend, 255, 255, 255, 255);
			rec = (SDL_Rect){x, ((s.top - j) * h) + (WIN_H - STACK_H),
				(s.tab[j].equiv + 1) * (STACK_W - 40) / (height + 1), h};
			SDL_RenderFillRect(data->rend, &rec);
		}
	}
}

void	draw(t_sdl *data, t_indexed_stack a, t_indexed_stack b)
{
	if (SDL_SetRenderDrawColor(data->rend, 0, 0, 0, 255) != 0)
		sdl_error("Get color failed");
	SDL_RenderClear(data->rend);
	visualisator(data, a, 0, a.top + b.top + 2);
	visualisator(data, b, STACK_W + 40, a.top + b.top + 2);
	write_text(data, "Stack A", 200);
	write_text(data, "Stack B", STACK_W + 200);
	if (data->vis_col)
	{
		if (SDL_SetRenderDrawColor(data->rend, 255, 0, 255, 255) != 0)
			sdl_error("Get color failed");
	}
	else
		if (SDL_SetRenderDrawColor(data->rend, 255, 255, 255, 255) != 0)
			sdl_error("Get color failed");
	if (SDL_RenderDrawLine(data->rend, WIN_W / 2, 0, WIN_W / 2, WIN_H) != 0)
		sdl_error("Get line failed");
	if (SDL_RenderDrawLine(data->rend, 0, WIN_H - STACK_H,
			WIN_W, WIN_H - STACK_H) != 0)
		sdl_error("Get line failed");
	SDL_RenderPresent(data->rend);
	event_listner();
	SDL_Delay(convert_range(a.top + b.top + 2,
			(t_range){0, 500}, (t_range){100, 0}));
	event_listner();
}

void	loop_program(t_sdl *data)
{
	SDL_bool	prog_launched;

	prog_launched = SDL_TRUE;
	while (prog_launched)
		event_listner();
	TTF_CloseFont(data->font);
	TTF_Quit();
	SDL_DestroyRenderer(data->rend);
	SDL_DestroyWindow(data->win);
	SDL_Quit();
}
