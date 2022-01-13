#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
#include "./libft/libft.h"
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
    int index;
    int value;
}               t_indexed_value;

typedef struct s_indexed_stack
{
    struct s_indexed_value *tab;
    int             top;
}              t_indexed_stack;

typedef struct  s_merge_tools
{
    int i;
    int j;
    int k;
    int n1;
    int n2;
}               t_merge_tools;

void    is_valid_args(char *arg);
void    is_doubling(t_stack s);
void    is_doubling_indexed(t_indexed_stack s);
int     is_valid_instruction(char *instr);
void    error(char *msg);
void    is_int_range(char *number, char min_int[11], char max_int[10]);
void    manage_instruction(t_stack *sa, t_stack *sb, char *instr);
void    manage_instruction_indexed_stack(t_indexed_stack *sa, t_indexed_stack *sb, char *instr);
int     is_sorted_array(int *a, int n);
int     is_sorted_indexed_array(t_indexed_value *a, int n);
void    mergeSort(t_indexed_value *stack, int l, int r, int by_val);
#endif