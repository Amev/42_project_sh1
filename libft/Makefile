# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vame <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/09 10:19:00 by vame              #+#    #+#              #
#    Updated: 2015/02/02 13:30:29 by vame             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIB_TMP = temp.a

FLAGS = -c -g -Werror -Wextra -Wall

INC = ./libft_ext.h

TMP = $(INC:.h=.h.gch) ./gnl/get_next_line.h.gch ./printf/ft_printf.h.gch

SRC_PTF =	./printf/ft_printf.c ./printf/ptf_fonctions.c ./printf/ptf_flags.c \
			./printf/ptf_layout.c ./printf/ptf_print_sign.c \
			./printf/ptf_asterisk.c

SRC_GNL =	./gnl/get_next_line.c

BINAIRE = ./ft_printf.o ./ptf_fonctions.o ./ptf_flags.o ./ptf_layout.o \
		  ./ptf_print_sign.o ./ptf_asterisk.o ./get_next_line.o

all: $(NAME)

$(NAME): $(SRC)
		make -C libft/
		gcc -I libft/includes/ $(FLAGS) $(INC) $(SRC_PTF) $(SRC_GNL)
		ar rc $(LIB_TMP) $(BINAIRE)
		libtool -static -o $(NAME) ./libft/libft.a $(LIB_TMP)
		ranlib $(NAME)
		@rm -f $(LIB_TMP)

lib:
		make -C libft/ fclean
		make -C libft/

clean:
		rm -f $(BINAIRE) $(TMP)
		make -C libft/ clean

fclean: clean
		rm -f $(NAME)
		make -C libft/ fclean

re: fclean all
