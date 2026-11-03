/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:35:36 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 09:25:55 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_add_count(int *send, int written)
{
	if (written < 0)
		send[2] = 1;
	else
		send[1] += written;
}

static int	*ft_checker_hex(const char *str, va_list *arguments, int *send)
{
	char			*pointer_value;
	unsigned long	return_value;

	if (str[send[0]] == 'X' || str[send[0]] == 'x')
	{
		return_value = va_arg(*arguments, unsigned int);
		if (str[send[0]] == 'x')
			pointer_value = ft_make_hex(return_value, 1);
		else
			pointer_value = ft_make_hex(return_value, 0);
		ft_add_count(send, ft_putstr(pointer_value));
	}
	else if (str[send[0]] == 'p')
	{
		return_value = va_arg(*arguments, uintptr_t);
		ft_add_count(send, ft_putptr(return_value));
	}
	else if (str[send[0]] == '\0')
		send[2] = 1;
	else
	{
		ft_add_count(send, ft_putchar('%'));
		ft_add_count(send, ft_putchar(str[send[0]]));
	}
	return (send);
}

static int	*ft_checker_decimal(const char *str, va_list *arguments, int *send)
{
	int	return_value;

	if (str[send[0]] == 'i' || str[send[0]] == 'd')
	{
		return_value = va_arg(*arguments, int);
		ft_add_count(send, ft_putnbr(return_value));
	}
	else if (str[send[0]] == 'u')
	{
		return_value = va_arg(*arguments, unsigned int);
		ft_add_count(send, ft_putunbr(return_value));
	}
	else
		send = ft_checker_hex(str, arguments, send);
	return (send);
}

int	*ft_checker_text(const char *str, va_list *arguments, int *send)
{
	int		return_value;
	char	*pointer_value;

	if (str[send[0]] == 'c' || str[send[0]] == '%')
	{
		if (str[send[0]] == 'c')
			return_value = va_arg(*arguments, int);
		else
			return_value = '%';
		ft_add_count(send, ft_putchar(return_value));
	}
	else if (str[send[0]] == 's')
	{
		pointer_value = va_arg(*arguments, char *);
		ft_add_count(send, ft_putstr(pointer_value));
	}
	else
		send = ft_checker_decimal(str, arguments, send);
	return (send);
}
