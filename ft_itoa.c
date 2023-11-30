/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:15:56 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/30 08:39:47 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	num_digit(long num)
{
	int	digits;

	digits = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		digits++;
	while (num != 0)
	{
		num = num / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(long n)
{
	long	len;
	long	nl;
	char	*result;

	len = num_digit(n);
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
