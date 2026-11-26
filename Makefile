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
include mk/hint.mk
include mk/config.mk
include mk/sources.mk

all: $(NAME)

$(NAME): $(OBJS)
	@$(call run,$(AR) $(NAME) $(OBJS))

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(call run,$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@)

clean:
	@$(call remove,$(BUILD_DIR),Removing the objects of ft_printf,objects of ft_printf)

fclean: clean
	@$(call remove,$(NAME),Removing the library $(NAME))

re: fclean all

# Every rule rebuilds the image, so it always tests the current sources
# (docker's cache makes this instant when nothing changed).
docker-build:
	docker build -t $(DOCKER_IMAGE) .

# An interactive shell exits with the status of its last command, which says
# nothing about the rule: only 125, docker itself failing, is an error.
docker-shell: docker-build
	@docker run --rm -it $(DOCKER_IMAGE) bash || [ $$? -ne 125 ]

# There are no checks: the image builds libftprintf.a from scratch on Linux, with
# the flags of mk/config.mk, so the exit status says whether it compiles.
docker-mandatory: docker-build
	docker run --rm $(DOCKER_IMAGE) make re

# Removes the test image once you are done with it.
docker-clean:
	@if docker image inspect $(DOCKER_IMAGE) >/dev/null 2>&1; then \
		$(call explain,Removing the docker image $(DOCKER_IMAGE)); \
		$(call run,docker rmi $(DOCKER_IMAGE)); \
	else \
		$(call warn,nothing to remove: there is no docker image $(DOCKER_IMAGE)); \
	fi

.PHONY: all clean fclean re \
	docker-build docker-shell docker-mandatory docker-clean
