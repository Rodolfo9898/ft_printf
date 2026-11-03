/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:54:25 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 09:25:55 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	char	character;

	character = c;
	if (write(1, &character, 1) != 1)
		return (-1);
	return (1);
}

int	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		if (ft_putchar(s[i]) < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_putnbr_base(uintmax_t number, const char *base)
{
	uintmax_t	base_length;
	int			count;

	base_length = 0;
	while (base[base_length])
		base_length++;
	count = 0;
	if (number >= base_length)
	{
		count = ft_putnbr_base(number / base_length, base);
		if (count < 0)
			return (-1);
	}
	if (ft_putchar(base[number % base_length]) < 0)
		return (-1);
	return (count + 1);
}

int	ft_putnbr(int number)
{
	long	value;
	int		count;
	int		written;

	value = number;
	count = 0;
	if (value < 0)
	{
		if (ft_putchar('-') < 0)
			return (-1);
		value = -value;
		count = 1;
	}
	written = ft_putnbr_base(value, DECIMAL);
	if (written < 0)
		return (-1);
	return (count + written);
}

int	ft_putptr(void *p)
{
	int	count;

	if (!p)
		return (ft_putstr(NULL_PTR_STR));
	if (ft_putstr("0x") < 0)
		return (-1);
	count = ft_putnbr_base((uintptr_t)p, HEX_LOWER);
	if (count < 0)
		return (-1);
	return (count + 2);
}
