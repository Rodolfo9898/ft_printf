/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:09:20 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/29 16:40:40 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	size_t	index;
	va_list	arguments;

	va_start(arguments, format);
	index = 0;
	while (format[index] != '\0')
	{
		if (format[index] != '%')
			ft_putchar_fd(format[index], 1);
		else
		{
			index++;
			index = ft_switch(format, index, arguments);
		}
		index++;
	}
	va_end(arguments);
	return (index);
}
/*
int	main(void)
{
	ft_printf("TesTing out\n%s\n%c\n%x\n%X\n%%\n%d", "HEY", '1', 15, -15, -5);
	return (0);
}*/