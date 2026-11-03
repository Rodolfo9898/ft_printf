/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_print.c                                 :+:      :+:    :+:   */
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

int	ft_putstr(char *s)
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

int	ft_putnbr(int n)
{
	int		count;
	char	*num;

	num = ft_itoa(n);
	if (!num)
		return (-1);
	count = ft_putstr(num);
	free(num);
	return (count);
}

int	ft_putunbr(unsigned int n)
{
	int		count;
	char	*num;

	num = ft_itoa(n);
	if (!num)
		return (-1);
	count = ft_putstr(num);
	free(num);
	return (count);
}

int	ft_putptr(uintptr_t p)
{
	int		count;
	char	*address;

	if (!p)
		return (ft_putstr("(nil)"));
	if (ft_putchar('0') < 0 || ft_putchar('x') < 0)
		return (-1);
	address = ft_make_hex(p, 1);
	count = ft_putstr(address);
	if (count < 0)
		return (-1);
	return (count + 2);
}
