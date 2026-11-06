# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 14:34:39 by rperez-t          #+#    #+#              #
#    Updated: 2026/11/03 11:41:28 by rperez-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include mk/colors.mk

NAME		= libftprintf.a

SRCS		= ft_print_utils.c ft_dispatch.c ft_printf.c

OBJS		= ${SRCS:.c=.o}

CC			= cc
CFLAGS		= -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${OBJS}
	@$(call run,ar rcs ${NAME} ${OBJS})

%.o: %.c ft_printf.h
	@$(call run,${CC} ${CFLAGS} -I . -c $< -o $@)

clean:
	@$(call remove,${OBJS},Removing the objects of ft_printf,objects of ft_printf)

fclean: clean
	@$(call remove,${NAME},Removing the library ${NAME})

re: fclean all

.PHONY: all clean fclean re
