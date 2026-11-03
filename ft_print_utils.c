/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:54:25 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 11:02:57 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putchar(int c)
{
	char	character;

	character = c;
	if (write(1, &character, 1) != 1)
		return (-1);
	return (1);
}

/* A string longer than INT_MAX could not be counted in the int return. */
int	pf_putstr(const char *s)
{
	size_t	length;
	size_t	done;
	ssize_t	written;

	if (!s)
		return (pf_putstr("(null)"));
	length = 0;
	while (s[length])
		length++;
	if (length > INT_MAX)
		return (-1);
	done = 0;
	while (done < length)
	{
		written = write(1, s + done, length - done);
		if (written <= 0)
			return (-1);
		done += written;
	}
	return ((int)length);
}

/* Base 2 needs the most digits: one per bit of a uintmax_t. */
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
	if (write(1, digits + sizeof(digits) - length, length) != length)
		return (-1);
	return (length);
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
