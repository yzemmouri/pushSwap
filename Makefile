# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/22 16:14:13 by yzemmour          #+#    #+#              #
#    Updated: 2020/02/22 15:55:05 by yzemmour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PUSH	= 	push_swap.c\
				is_valid_args.c\
				error.c\
				is_int_range.c\
				manage_instruction_indexed_stack.c\
				is_sorted_array.c\
				visualisator.c\
			
SRC_CHECKER	=	manage_instruction.c\
				is_sorted_array.c\
				is_valid_args.c\
				error.c\
				is_int_range.c\
				checker.c\

HEADER 	= 	push_swap.h\
			

OBJ_PUSH = $(addprefix $(OBJ_DIR_PUSH)/,$(SRC_PUSH:.c=.o))

OBJ_CHECKER = $(addprefix $(OBJ_DIR_CHECKER)/,$(SRC_CHECKER:.c=.o))

PROG_PUSH = push_swap

PROG_CHECKER = checker

CFLAGS = -Wall -Wextra -Werror -g

INCLUDE	= -I/Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/include \
		-I/Users/$$USER/.brew/Cellar/sdl2_ttf/2.0.15/include

LIB = -L /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/lib \
		-L /Users/$$USER/.brew/Cellar/sdl2_ttf/2.0.15/lib

SDL = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_ttf

SRC_DIR = ./src

OBJ_DIR_CHECKER = ./obj_checker

OBJ_DIR_PUSH = ./obj_push

LIBFT_DIR = ./libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a


CC = @gcc 

all : dirs $(PROG_CHECKER) $(PROG_PUSH)

dirs :
	@mkdir -p $(OBJ_DIR_CHECKER) $(OBJ_DIR_PUSH)

$(LIBFT_LIB): force
	@make -C $(LIBFT_DIR)

force:

$(PROG_PUSH) : $(LIBFT_LIB) $(OBJ_PUSH)
	@gcc $(OBJ_PUSH) $(CFLAGS) -o $(PROG_PUSH) $(INCLUDE) $(LIB)  $(SDL) $(LIBFT_LIB)
	@echo "\033[92mDone for push_swap\033[0m"

$(PROG_CHECKER) : $(LIBFT_LIB) $(OBJ_CHECKER)
	@gcc $(OBJ_CHECKER) $(CFLAGS) -o $(PROG_CHECKER) $(INCLUDE) $(LIB)  $(SDL) $(LIBFT_LIB)
	@echo "\033[92mDone for checker\033[0m"


$(OBJ_DIR_PUSH)/%.o : $(SRC_DIR)/%.c $(HEADER)
	@gcc -c  $(INCLUDE) $< -o $@ 

$(OBJ_DIR_CHECKER)/%.o : $(SRC_DIR)/%.c $(HEADER)
	@gcc -c  $(INCLUDE) $< -o $@

clean :
	@make clean -C ./libft/
	@rm -rf $(OBJ_DIR_PUSH)
	@rm -rf $(OBJ_DIR_CHECKER)

fclean : clean
	@make fclean -C ./libft/
	@rm -rf $(PROG_PUSH)
	@rm -rf $(PROG_CHECKER)

norme:
	@norminette $(SRC_DIR)

re : fclean all
