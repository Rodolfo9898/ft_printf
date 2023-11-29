/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:09:20 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/29 21:39:37 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		*ret;
	int		send[2];
	va_list	arguments;

	va_start(arguments, format);
	send[0] = 0;
	send[1] = 0;
	while (format[send[0]] != '\0')
	{
		if (format[send[0]] != '%')
			send[1] += ft_putchar(format[send[0]]);
		else
		{
			send[0]++;
			ret = ft_switch(format, arguments, send);
			send[0] = ret[0];
			send[1] = ret[1];
		}
		send[0]++;
	}
	va_end(arguments);
	return (send[1]);
}
/*
int	main(void)
{
	ft_printf("TesTing out\n%s\n%c\n%x\n%X\n%%\n%d", "HEY", '1', 15, -15, -5);
	return (0);
}*/