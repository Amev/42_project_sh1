# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vame <vame@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/23 11:23:10 by vame              #+#    #+#              #
#    Updated: 2015/03/06 12:57:24 by vame             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell1

CFLAGS = -c -g -Werror -Wextra -Wall

INC = ./ft_sh1.h

TMP = $(INC:.h=.h.gch)

SRC =	./sh_o_main.c \
		./sh_o_builtins.c \
		./sh_o_tools.c \
		./sh_o_cmd.c \
		./sh_o_env.c \
		./sh_o_cd.c \
		./sh_o_cd_algo.c \
		./sh_o_data.c \
		./sh_o_env_builtin.c \
		./sh_o_setenv.c

BINAIRE = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(BINQIRE)
		make -C libft/
		gcc -I libft/includes/ $(CFLAGS) $(INC) $(SRC)
		gcc -o $(NAME) $(BINAIRE) -L libft/ -lft
		@rm -f $(TMP)

lib :
		make -C libft/ fclean
		make -C libft/

clean:
		rm -f $(BINAIRE)
		make -C libft/ clean

fclean: clean
		rm -f $(NAME)
		make -C libft/ fclean

re: fclean all

.PHONY: all lib clean fclean re
