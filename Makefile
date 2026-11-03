# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 14:34:39 by rperez-t          #+#    #+#              #
#    Updated: 2026/11/03 10:01:45 by rperez-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

SRCS		= ft_print_utils.c ft_switcher.c ft_printf.c

OBJS		= ${SRCS:.c=.o}

CC			= cc
CFLAGS		= -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

%.o: %.c ft_printf.h
	${CC} ${CFLAGS} -I . -c $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
