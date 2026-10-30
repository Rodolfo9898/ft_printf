/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:15:56 by rperez-t          #+#    #+#             */
/*   Updated: 2026/10/30 16:18:32 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_digit(long num, int base)
{
	int	digits;

	digits = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		digits++;
	while (num != 0)
	{
		num = num / base;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(long n)
{
	long	len;
	long	nl;
	char	*result;

	len = num_digit(n, 10);
	nl = n;
	if (n < 0)
		nl *= -1;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = 0;
	if (nl == 0)
		result[0] = '0';
	else
	{
		while (len--, nl != 0)
		{
			result[len] = (nl % 10) + '0';
			nl = (nl - (nl % 10)) / 10;
		}
		if (n < 0)
			result[len] = '-';
	}
	return (result);
}

char	*ft_make_hex(unsigned long num, int lowercase)
{
	static char	rep[] = "0123456789ABCDEF";
	static char	buffer[100];
	char		*ptr;

	ptr = &buffer[99];
	*ptr = '\0';
	if (num == 0)
		*--ptr = rep[0];
	else
	{
		while (num != 0)
		{
			if (lowercase && 9 < num % 16)
				*--ptr = rep[num % 16] + 32;
			else
				*--ptr = rep[num % 16];
			num /= 16;
		}
	}
	return (ptr);
}
