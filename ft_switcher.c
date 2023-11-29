/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:35:36 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/29 15:24:01 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int	ft_switch2(char *str, int index, va_list arguments)
{
	int		return_value;
	char	*pointer_value;

	if (str[index] == 'X' || str[index] == 'x')
	{
		return_value = va_arg(arguments, unsigned int);
		if (str[index] == 'x')
			pointer_value = ft_make_hex(return_value, 1);
		else
			pointer_value = ft_make_hex(return_value, 0);
		ft_putstr_fd(pointer_value, 1);
	}
	return (index);
}

int	ft_switch(char *str, int index, va_list arguments)
{
	int		return_value;
	char	*pointer_value;

	if (str[index] == 'c' || str[index] == '%')
	{
		if (str[index] == 'c')
			return_value = va_arg(arguments, int);
		else
			return_value = '%';
		ft_putchar_fd(return_value, 1);
	}
	else if (str[index] == 's')
	{
		pointer_value = va_arg(arguments, char *);
		ft_putstr_fd(pointer_value, 1);
	}
	else if (str[index] == 'i' || str[index] == 'd')
	{
		return_value = va_arg(arguments, int);
		ft_putnbr_fd(return_value, 1);
	}
	else
		index = ft_switch2(str, index, arguments);
	return (index);
}
