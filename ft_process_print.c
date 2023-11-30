/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:54:25 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/30 08:57:57 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
		i += ft_putchar(s[i]);
	return (i);
}

int	ft_putnbr(int n)
{
	int		count;
	char	*num;

	num = ft_itoa(n);
	count = ft_putstr(num);
	free(num);
	return (count);
}

int	ft_putunbr(unsigned int n)
{
	int		count;
	char	*num;

	num = ft_itoa(n);
	count = ft_putstr(num);
	free(num);
	return (count);
}
