#include "../push_swap.h"

void			sdl_error(char *message)
{
	SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();
	exit(-1);
}

int convert_range(int n, int old_min, int old_max, int new_min, int new_max)
{
    return ((((n - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min);
}

void    event_listner()
{
    SDL_Event	event;

    if (SDL_PollEvent(&event))
    {
        if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                    || event.type == SDL_QUIT)
        {
            // // ft_free_obj(data);
            // prog_launched = SDL_FALSE;
            exit(1);
        }
    }
}

uint32_t rgb(double ratio)
{
    int normalized = (int)(ratio * 256 * 4);
    int region = normalized / 256;
    int x = normalized % 256;

    uint8_t r = 0, g = 0, b = 0;
    switch (region)
    {
    case 0: r = 255; g = 0;   b = 0;   g += x; break;
    case 1: r = 255; g = 255; b = 0;   r -= x; break;
    case 2: r = 0;   g = 255; b = 0;   b += x; break;
    case 3: r = 0;   g = 255; b = 255; g -= x; break;
    }
    return r | (g << 8) | (b << 16);
}

void			init_sdl(t_sdl *data)
{
	data->win = NULL;
	    //this opens a font style and sets a size
    
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		sdl_error("initialisation SDL");
	if (!(data->win = SDL_CreateWindow("PUSH SWAP :)", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN)))
		sdl_error("Creation window");
	if (!(data->rend = SDL_CreateRenderer(data->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		sdl_error("Creation render");
	if (SDL_SetRenderDrawColor(data->rend, 0, 0, 0, 255) != 0)
		sdl_error("Get color failed");
     if( TTF_Init() != 0)
         sdl_error("Font init error");

    data->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 500);

    if (data->font == NULL)
    {
        sdl_error("Font error");
    }
    // if (SDL_RenderDrawPoint(data->rend, 0,0) != 0)
    //     sdl_error("Get draw failed");
    SDL_PumpEvents();
}

void            write_text(t_sdl *data,char *str, int x)
{

// this is the color in rgb format,
// maxing out all would give you the color white,
// and it will be your text's color
SDL_Color white = {255, 255, 255};
if (is_option_activated(data->options, C_OPTION))
    white = (SDL_Color){255, 0, 255};
// as TTF_RenderText_Solid could only be used on
// SDL_Surface then you have to create the surface first
SDL_Surface* surfaceMessage =
    TTF_RenderText_Solid(data->font, str, white); 

// now you can convert it into a texture
SDL_Texture* Message = SDL_CreateTextureFromSurface(data->rend, surfaceMessage);

SDL_Rect Message_rect; //create a rect
Message_rect.x = x;  //controls the rect's x coordinate 
Message_rect.y = 0; // controls the rect's y coordinte
Message_rect.w = STACK_W - 80; // controls the width of the rect
Message_rect.h = WIN_H - STACK_H; // controls the height of the rect

// (0,0) is on the top left of the window/screen,
// think a rect as the text's box,
// that way it would be very simple to understand

// Now since it's a texture, you have to put RenderCopy
// in your game loop area, the area where the whole code executes

// you put the renderer's name first, the Message,
// the crop size (you can ignore this if you don't want
// to dabble with cropping), and the rect which is the size
// and coordinate of your texture
SDL_RenderCopy(data->rend, Message, NULL, &Message_rect);

// Don't forget to free your surface and texture
SDL_FreeSurface(surfaceMessage);
SDL_DestroyTexture(Message);
}
void            draw(t_sdl *data, t_indexed_stack a, t_indexed_stack b)
{
    if (SDL_SetRenderDrawColor(data->rend, 0, 0, 0, 255) != 0)
	    sdl_error("Get color failed");
	SDL_RenderClear(data->rend);
    Visualisator(data, a, 0, a.top + b.top + 2);
    Visualisator(data, b, STACK_W + 40, a.top + b.top + 2);
    write_text(data, "Stack A", 0);
    write_text(data, "Stack B", STACK_W + 40);
    if (is_option_activated(data->options, C_OPTION))
    {
        if (SDL_SetRenderDrawColor(data->rend, 255, 0, 255, 255) != 0)
            sdl_error("Get color failed");
    }
    else
        if (SDL_SetRenderDrawColor(data->rend, 255, 255, 255, 255) != 0)
            sdl_error("Get color failed");
    if (SDL_RenderDrawLine(data->rend, WIN_W / 2, 0, WIN_W / 2, WIN_H) != 0)
        sdl_error("Get line failed");
    if (SDL_RenderDrawLine(data->rend, 0, WIN_H - STACK_H, WIN_W, WIN_H - STACK_H) != 0)
        sdl_error("Get line failed");
    SDL_RenderPresent(data->rend);
    event_listner();
    SDL_Delay(convert_range(a.top + b.top + 2, 0, 500, 100, 0));
    event_listner();
    // printf("draaw\n");
}

void			Visualisator(t_sdl *data, t_indexed_stack s, int x, int height)
{
	int			j;
    int         color;
    int h;

	j = 0;
    if (s.top >= 0)
    {
        h = STACK_H / height;
        while (j <= s.top)
        {
            if (is_option_activated(data->options, C_OPTION))
            {
                color = rgb((double)(s.tab[j].equiv) / height);
                if (SDL_SetRenderDrawColor(data->rend,
                            color & 0x0000FF, (color & 0x00FF00) >> 8, (color & 0xFF0000) >> 16, 255) != 0)
                  sdl_error("Get color failed");
            }
            else
                if (SDL_SetRenderDrawColor(data->rend,
                            255, 255, 255, 255) != 0)
                  sdl_error("Get color failed");
            SDL_Rect rec;
            rec.x = x;
            rec.y = ((s.top - j) * h) + (WIN_H - STACK_H);
            rec.w = (s.tab[j].equiv + 1) * (STACK_W - 40)/(height + 1);
            rec.h = h;

            if (SDL_RenderFillRect(data->rend, &rec) != 0)
                sdl_error("draw rectangle failed");
            j++;
        }
    }
	
	// return (NULL);
}

void			loop_program(t_sdl *data)
{
	SDL_bool	prog_launched;

	
	prog_launched = SDL_TRUE;
	while (prog_launched)
	{
		event_listner();
	}

    TTF_CloseFont(data->font);
    TTF_Quit();
	SDL_DestroyRenderer(data->rend);
	SDL_DestroyWindow(data->win);
	SDL_Quit();
}