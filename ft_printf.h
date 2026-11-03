/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:47:13 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 11:41:28 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>

/* The libc printf prints a NULL %p as "0x0" on macOS and "(nil)" on Linux. */
# ifdef __APPLE__
#  define NULL_PTR_STR "0x0"
# else
#  define NULL_PTR_STR "(nil)"
# endif

# define DECIMAL "0123456789"
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"

typedef struct s_state
{
	size_t	pos;
	int		count;
	int		error;
}	t_state;

int		pf_write_all(const char *buffer, size_t length);
int		pf_putchar(int c);
int		pf_putstr(const char *s);
int		pf_putptr(void *p);
int		pf_putnbr(int number);
int		pf_putnbr_base(uintmax_t number, const char *base);
void	pf_add_count(t_state *state, int written);
void	pf_dispatch(const char *format, va_list *arguments, t_state *state);
int		ft_printf(const char *format, ...);

#endif
