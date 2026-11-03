/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:35:36 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 11:56:22 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* write may stop early, so loop; more than INT_MAX bytes cannot be counted. */
int	pf_write_all(const char *buffer, size_t length)
{
	size_t	done;
	ssize_t	written;

	if (length > INT_MAX)
		return (-1);
	done = 0;
	while (done < length)
	{
		written = write(1, buffer + done, length - done);
		if (written <= 0)
			return (-1);
		done += written;
	}
	return ((int)length);
}

void	pf_add_count(t_state *state, int written)
{
	if (written < 0 || written > INT_MAX - state->count)
		state->error = 1;
	else
		state->count += written;
}

static int	pf_print_unknown(char specifier)
{
	char	sequence[2];

	sequence[0] = '%';
	sequence[1] = specifier;
	return (pf_write_all(sequence, 2));
}

int	pf_print_conversion(char specifier, va_list *arguments)
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
