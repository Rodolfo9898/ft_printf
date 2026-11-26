# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/07 00:00:00 by rperez-t          #+#    #+#              #
#    Updated: 2026/11/07 00:00:00 by rperez-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
AR			= ar rcs

BUILD_DIR	= build
# The objects, in build/; the archive stays at the root.
OBJ_DIR		= $(BUILD_DIR)/mandatory
DOCKER_IMAGE	= ft_printf-test
