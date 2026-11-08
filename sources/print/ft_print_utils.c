/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:54:25 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 14:51:49 by rperez-t         ###   ########.fr       */
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

int	pf_putchar(int c)
{
	char	character;

	character = c;
	return (pf_write_all(&character, 1));
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
