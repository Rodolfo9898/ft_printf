/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:35:36 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 10:01:45 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_add_count(t_state *state, int written)
{
	if (written < 0 || written > INT_MAX - state->count)
		state->error = 1;
	else
		state->count += written;
}

static int	ft_print_unknown(char specifier)
{
	if (ft_putchar('%') < 0 || ft_putchar(specifier) < 0)
		return (-1);
	return (2);
}

static int	ft_print_conversion(char specifier, va_list *arguments)
{
	if (specifier == 'c')
		return (ft_putchar(va_arg(*arguments, int)));
	if (specifier == 's')
		return (ft_putstr(va_arg(*arguments, char *)));
	if (specifier == 'p')
		return (ft_putptr(va_arg(*arguments, void *)));
	if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(*arguments, int)));
	if (specifier == 'u')
		return (ft_putnbr_base(va_arg(*arguments, unsigned int), DECIMAL));
	if (specifier == 'x')
		return (ft_putnbr_base(va_arg(*arguments, unsigned int), HEX_LOWER));
	if (specifier == 'X')
		return (ft_putnbr_base(va_arg(*arguments, unsigned int), HEX_UPPER));
	if (specifier == '%')
		return (ft_putchar('%'));
	return (ft_print_unknown(specifier));
}

void	ft_dispatch(const char *format, va_list *arguments, t_state *state)
{
	char	specifier;

	specifier = format[state->pos];
	if (specifier == '\0')
		state->error = 1;
	else
		ft_add_count(state, ft_print_conversion(specifier, arguments));
}
