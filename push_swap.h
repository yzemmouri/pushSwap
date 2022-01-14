#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# define WIN_W       1280
# define WIN_H       1100
# define STACK_H     1000
#define STACK_W 640
# define V_OPTION 0
# define C_OPTION 1
#include "./libft/libft.h"
#include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"


#include <stdio.h>

typedef struct              s_instruction
{
    char                    *value;
    struct  s_instruction   *next;
}                           t_instruction;


typedef struct s_stack
{
    int *tab;
    int top;
}              t_stack;

typedef struct  s_indexed_value
{
    int equiv;
    int index;
    int value;
}               t_indexed_value;

typedef struct s_indexed_stack
{
    struct s_indexed_value *tab;
    int             top;
}              t_indexed_stack;

typedef struct  s_merge
{
    int i;
    int j;
    int k;
    int n1;
    int n2;
}               t_merge;

typedef struct s_merge_param
{
    int     r;
    int     l;
    int     m;
}               t_merge_param;

typedef struct s_sdl
{
    SDL_Window			*win;
	SDL_Renderer		*rend;
    char              options:2;
    TTF_Font            *font;
}               t_sdl;


void    is_valid_args(char *arg);
void    is_doubling(t_stack s);
void    is_doubling_indexed(t_indexed_stack s);
int     is_valid_instruction(char *instr);
void    error(char *msg);
void    is_int_range(char *number, char min_int[11], char max_int[10]);
void    manage_instruction(t_stack *sa, t_stack *sb, char *instr);
void    manage_instruction_indexed_stack(t_sdl *data, t_indexed_stack *sa, t_indexed_stack *sb, char *instr);
int     is_sorted_array(int *a, int n);
int     is_sorted_indexed_array(t_indexed_value *a, int n);
void    merge_sort(t_indexed_value *stack, int l, int r, int by_val);
void	init_sdl(t_sdl *data);
void	loop_program(t_sdl *data);
void	sdl_error(char *message);
void	Visualisator(t_sdl *data, t_indexed_stack s, int x, int height);
void    draw(t_sdl *data, t_indexed_stack a, t_indexed_stack b);
char    is_option_activated(char option, int option_index);
#endif