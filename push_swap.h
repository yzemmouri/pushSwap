/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 07:55:11 by yzemmour          #+#    #+#             */
/*   Updated: 2022/03/23 07:55:15 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define WIN_W		1280
# define WIN_H		1100
# define STACK_H	1000
# define STACK_W	640

# include "./libft/libft.h"
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "stdio.h"

typedef struct s_instuction
{
	char					*value;
	struct s_instuction		*next;
}	t_inst;

typedef struct s_stack
{
	int						*tab;
	int						top;
}	t_stack;

typedef struct s_indexed_value
{
	int						equiv;
	int						index;
	int						value;
}	t_indexed_value;

typedef struct s_indexed_stack
{
	struct s_indexed_value	*tab;
	int						top;
}	t_indexed_stack;

typedef struct s_merge
{
	int						i;
	int						j;
	int						k;
	int						n1;
	int						n2;
	int						type;
}	t_merge;

typedef struct s_merge_param
{
	int						r;
	int						l;
	int						m;
}	t_merge_param;

typedef struct s_sdl
{
	SDL_Window				*win;
	SDL_Renderer			*rend;
	int						is_visu;
	int						vis_col;
	TTF_Font				*font;
}	t_sdl;

typedef struct s_env
{
	t_indexed_stack			a;
	t_indexed_stack			b;
	t_inst					*insts;
	t_inst					*inst_index;
	t_sdl					sdl;
	int						temp;
	int						n;
	int						m;
	int						fl;
}	t_env;

typedef struct s_len
{
	int						rb;
	int						rrb;
}	t_len;

typedef struct s_var_best_elem
{
	int						min_num_op;
	int						len;
	int						best_index;
	int						new_max_min;
	int						i;
}	t_var_best_elem;

typedef struct s_range
{
	int						min;
	int						max;
}	t_range;

typedef struct s_color
{
	uint8_t					r;
	uint8_t					g;
	uint8_t					b;
}	t_color;

void		is_valid_args(char *arg);
void		is_doubling(t_stack s);
void		is_doubling_indexed(t_indexed_stack s);
int			is_valid_instuction(char *inst);
void		five_elems(t_env *env);
void		three_elems(t_env *env);
void		error(char *msg);
void		is_int_range(char *number, char min_int[11], char max_int[10]);
void		manage_instuction(t_stack *sa, t_stack *sb, char *inst);
void		sx_inst(t_stack *s);
void		ss_inst(t_stack *s1, t_stack *s2);
void		px_inst(t_stack *s1, t_stack *s2);
void		rot_inst(t_stack *s, int to_up);
void		rot_rot_inst(t_stack *sa, t_stack *sb, int to_up);
t_inst		*add_inst(t_inst *insts, char *oper);
void		op_inst(t_env *env, char *op);
void		print_insts(t_inst *insts);
t_inst		*put_elem_top_b(t_env *env, int num, t_inst *inst_b);
t_inst		*put_elem_top_a(t_env *env, int num, t_inst *inst, int c);
t_inst		*put_elem_position(t_env *env, t_inst *inst_a,
				t_inst *inst_b, int c);
t_inst		*push_b_op(t_env *env, t_inst *inst_a, t_inst *inst_b, int c);
int			best_elem(t_env *env);
t_inst		*positon_in_a(t_env *env, t_inst *insts_a, t_inst *insts_b);
void		manage_indexed_stack(t_sdl *data, t_indexed_stack *sa,
				t_indexed_stack *sb, char *inst);
void		sx_inst_indexed(t_indexed_stack *s);
void		ss_inst_indexed(t_indexed_stack *s1, t_indexed_stack *s2);
void		px_inst_indexed(t_indexed_stack *s1, t_indexed_stack *s2);
void		rot_inst_indexed(t_indexed_stack *s, int to_up);
void		rot_rot_inst_indexed(t_indexed_stack *a,
				t_indexed_stack *b, int to_up);
int			is_sorted_array(int *a, int n);
int			is_sorted_indexed_array(t_indexed_value *a, int n);
void		merge_sort(t_indexed_value *stack, int l, int r, int by_val);
void		init_sdl(t_sdl *data);
void		loop_program(t_sdl *data);
void		sdl_error(char *message);
void		Visualisator(t_sdl *data, t_indexed_stack s, int x, int height);
void		draw(t_sdl *data, t_indexed_stack a, t_indexed_stack b);
char		is_option_activated(char option, int option_index);
t_inst		*fusion(t_inst *insts, t_inst *insts_a, t_inst *insts_b);
t_inst		*complex_sort(t_env *env);
int			five_max_min(t_indexed_stack s, int num);
// void		sdl_error(char *message);
// int			convert_range(int n, t_range old, t_range new);
// void		event_listner(void);
// uint32_t	rgb(double ratio);
t_inst		*free_insts(t_inst *insts);
#endif
