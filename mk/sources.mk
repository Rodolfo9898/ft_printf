# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/07 00:00:00 by rperez-t          #+#    #+#              #
#    Updated: 2026/11/07 00:00:00 by rperez-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ft_printf() alone in sources/ft_printf.c, the rest under sources/print/.
SRC_DIR		= sources
INC_DIR		= include
PRINT_SRCS	= ft_print_utils.c ft_dispatch.c ft_format.c
SRCS		= $(addprefix $(SRC_DIR)/print/,$(PRINT_SRCS)) $(SRC_DIR)/ft_printf.c
HEADERS		= $(INC_DIR)/ft_printf.h $(addprefix $(INC_DIR)/core/,libs.h defines.h structs.h)

OBJS		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
