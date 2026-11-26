# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    hint.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/26 12:23:05 by rperez-t          #+#    #+#              #
#    Updated: 2026/11/26 12:23:05 by rperez-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# A plain `make` that fails usually means a tool or a library is missing on this
# machine. It then says where everything is installed already: the docker container
# of make docker-shell (not inside that container, where it would make no sense).
# Only the plain `make` does it, not make clean, make re or any other goal. The
# build itself runs as it always did, in a second make (HINTED=1 stops that one from
# doing the same again), and its exit status is kept. A Ctrl-C says nothing.
# This is a library that other projects build with make -C: when one of them
# builds it (MAKELEVEL is not 0) it stays quiet, so that project's own make
# rules, plain or not, decide what is said.
ifeq ($(MAKECMDGOALS),)
ifndef HINTED
ifeq ($(MAKELEVEL),0)

.DEFAULT_GOAL := build-or-hint

build-or-hint:
	@$(MAKE) -f $(firstword $(MAKEFILE_LIST)) --no-print-directory HINTED=1 || { status=$$?; \
		[ $$status -ge 128 ] || [ -e /.dockerenv ] || [ -e /run/.containerenv ] || \
			printf '$(YELLOW)%s$(RESET)\n' \
			'dependencies missing: run make docker-shell to have them all inside the docker container' >&2; \
		exit $$status; }

.PHONY: build-or-hint

endif
endif
endif
