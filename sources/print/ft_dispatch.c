/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:35:36 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 13:15:37 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_print_unknown(char specifier)
{
	char	sequence[2];

	sequence[0] = '%';
	sequence[1] = specifier;
	return (pf_write_all(sequence, 2));
}

static int	pf_putstr(const char *s)
{
	size_t	length;

	if (!s)
		return (pf_putstr("(null)"));
	length = 0;
	while (s[length])
		length++;
	return (pf_write_all(s, length));
}

/* Negating in unsigned arithmetic is defined even for INT_MIN. */
static int	pf_putnbr(int number)
{
	unsigned int	magnitude;
	int				count;
	int				written;

	magnitude = number;
	count = 0;
	if (number < 0)
	{
		if (pf_putchar('-') < 0)
			return (-1);
		magnitude = -magnitude;
		count = 1;
	}
	written = pf_putnbr_base(magnitude, DECIMAL);
	if (written < 0)
		return (-1);
	return (count + written);
}

static int	pf_putptr(void *p)
{
	int	count;

	if (!p)
		return (pf_putstr(NULL_PTR_STR));
	if (pf_putstr("0x") < 0)
		return (-1);
	count = pf_putnbr_base((uintptr_t)p, HEX_LOWER);
	if (count < 0)
		return (-1);
	return (count + 2);
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
