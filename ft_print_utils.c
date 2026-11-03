/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:54:25 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 11:41:28 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putchar(int c)
{
	char	character;

	character = c;
	return (pf_write_all(&character, 1));
}

int	pf_putstr(const char *s)
{
	size_t	length;

	if (!s)
		return (pf_putstr("(null)"));
	length = 0;
	while (s[length])
		length++;
	return (pf_write_all(s, length));
}

/* Sized for the worst case, base 2: one digit per bit of a uintmax_t. */
int	pf_putnbr_base(uintmax_t number, const char *base)
{
	char		digits[sizeof(uintmax_t) * CHAR_BIT];
	uintmax_t	base_length;
	int			length;

	base_length = 0;
	while (base[base_length])
		base_length++;
	if (base_length < 2)
		return (-1);
	length = 0;
	while (length == 0 || number > 0)
	{
		length++;
		digits[sizeof(digits) - length] = base[number % base_length];
		number /= base_length;
	}
	return (pf_write_all(digits + sizeof(digits) - length, length));
}

/* Negating in unsigned arithmetic is defined even for INT_MIN. */
int	pf_putnbr(int number)
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

int	pf_putptr(void *p)
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
