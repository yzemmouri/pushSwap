#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
#include "./libft/libft.h"
#include <stdio.h>

typedef struct instruction instruction;
struct instruction
{
    char* value;
    instruction *suivant;
};

typedef struct s_stack
{
    int *tab;
    int top;
}              t_stack;

void    is_valid_args(char *arg);
void    is_doubling(t_stack s);
int     is_valid_instruction(char *instr);
void    error(char *msg);
void    is_int_range(char *number, char min_int[11], char max_int[10]);
void    manage_instruction(t_stack sa, t_stack sb, char *instr);
#endif