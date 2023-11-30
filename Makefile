# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 14:34:39 by rperez-t          #+#    #+#              #
#    Updated: 2023/11/28 18:35:18 by rperez-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

SRCS		= ft_itoa.c ft_make_hex.c ft_process_print.c\
			  ft_switcher.c ft_printf.c

OBJS		= ${SRCS:.c=.o}

FLAGS		= -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${OBJS}
	cc ${FLAGS} -c ${SRCS} -I ./
	ar rc ${NAME} ${OBJS}

.c.o:
		cc ${FLAGS} -I ./ -c $< -o ${<:.c=.o}

clean:
	rm -f ${OBJS} ${BONUS_OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean bonus
