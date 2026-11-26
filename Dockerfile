# Linux test image for ft_printf: builds libftprintf.a from scratch, with the
# flags of mk/config.mk (-Wall -Wextra -Werror), and has valgrind to test the
# library with your own programs. There are no checks: the image proves that the
# library builds on Linux. Its default command is make re: the exit status says
# whether it compiled.
#
#   make docker-mandatory                                  # make re in the image
#   make docker-shell                                      # bash inside the image
#   make docker-build && docker run --rm ft_printf-test    # the same, by hand
#   make docker-clean                                      # removes the image
FROM debian:trixie

RUN apt-get update \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
		build-essential valgrind \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /work
COPY . .
RUN make

CMD ["make", "re"]
