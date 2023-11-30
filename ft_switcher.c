/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:35:36 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/30 13:12:29 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
int	*ft_switch4(const char *str, va_list arguments, int *send)
{
	return (send);
}
*/
int	*ft_switch3(const char *str, va_list arguments, int *send)
{
	char			*pointer_value;
	unsigned long	return_value;

	if (str[send[0]] == 'X' || str[send[0]] == 'x')
	{
		return_value = va_arg(arguments, unsigned int);
		if (str[send[0]] == 'x')
			pointer_value = ft_make_hex(return_value, 1);
		else
			pointer_value = ft_make_hex(return_value, 0);
		send[1] += ft_putstr(pointer_value);
	}
	else if (str[send[0]] == 'p')
	{
		return_value = va_arg(arguments, uintptr_t);
		send[1] += ft_putptr(return_value);
	}
	return (send);
}

int	*ft_switch2(const char *str, va_list arguments, int *send)
{
	int	return_value;

	if (str[send[0]] == 'i' || str[send[0]] == 'd')
	{
		return_value = va_arg(arguments, int);
		send[1] += ft_putnbr(return_value);
	}
	else if (str[send[0]] == 'u')
	{
		return_value = va_arg(arguments, unsigned int);
		send[1] += ft_putunbr(return_value);
	}
	else
		send = ft_switch3(str, arguments, send);
	return (send);
}

int	*ft_switch(const char *str, va_list arguments, int *send)
{
	int		return_value;
	char	*pointer_value;

	if (str[send[0]] == 'c' || str[send[0]] == '%')
	{
		if (str[send[0]] == 'c')
			return_value = va_arg(arguments, int);
		else
			return_value = '%';
		send[1] += ft_putchar(return_value);
	}
	else if (str[send[0]] == 's')
	{
		pointer_value = va_arg(arguments, char *);
		send[1] += ft_putstr(pointer_value);
	}
	else
		send = ft_switch2(str, arguments, send);
	return (send);
}
