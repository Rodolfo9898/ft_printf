# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 14:34:39 by rperez-t          #+#    #+#              #
#    Updated: 2023/11/24 11:01:58 by rperez-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c\
			  ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
			  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
			  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BONUS_SRCS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			  ft_lstmap.c
				
OBJS		= ${SRCS:.c=.o}

BONUS_OBJS	= ${BONUS_SRCS:.c=.o}

FLAGS		= -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${OBJS}
	cc ${FLAGS} -c ${SRCS} -I ./
	ar rc ${NAME} ${OBJS}

.c.o:
		cc ${FLAGS} -I ./ -c $< -o ${<:.c=.o}

bonus: ${NAME}
	cc ${FLAGS} -c ${BONUS_SRCS} -I ./
	ar rc ${NAME} ${BONUS_OBJS}

clean:
	rm -f ${OBJS} ${BONUS_OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean bonus
