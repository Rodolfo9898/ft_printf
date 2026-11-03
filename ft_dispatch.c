/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:35:36 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 10:45:24 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_add_count(t_state *state, int written)
{
	if (written < 0 || written > INT_MAX - state->count)
		state->error = 1;
	else
		state->count += written;
}

static int	pf_print_unknown(char specifier)
{
	if (pf_putchar('%') < 0 || pf_putchar(specifier) < 0)
		return (-1);
	return (2);
}

static int	pf_print_conversion(char specifier, va_list *arguments)
{
	if (specifier == 'c')
		return (pf_putchar(va_arg(*arguments, int)));
	if (specifier == 's')
		return (pf_putstr(va_arg(*arguments, char *)));
	if (specifier == 'p')
		return (pf_putptr(va_arg(*arguments, void *)));
	if (specifier == 'd' || specifier == 'i')
		return (pf_putnbr(va_arg(*arguments, int)));
	if (specifier == 'u')
		return (pf_putnbr_base(va_arg(*arguments, unsigned int), DECIMAL));
	if (specifier == 'x')
		return (pf_putnbr_base(va_arg(*arguments, unsigned int), HEX_LOWER));
	if (specifier == 'X')
		return (pf_putnbr_base(va_arg(*arguments, unsigned int), HEX_UPPER));
	if (specifier == '%')
		return (pf_putchar('%'));
	return (pf_print_unknown(specifier));
}

void	pf_dispatch(const char *format, va_list *arguments, t_state *state)
{
	char	specifier;

	specifier = format[state->pos];
	if (specifier == '\0')
		state->error = 1;
	else
		pf_add_count(state, pf_print_conversion(specifier, arguments));
}
