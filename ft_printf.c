/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:09:20 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 09:25:55 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		*ret;
	int		send[3];
	va_list	arguments;

	va_start(arguments, format);
	send[0] = 0;
	send[1] = 0;
	send[2] = 0;
	while (send[2] == 0 && format[send[0]] != '\0')
	{
		if (format[send[0]] != '%')
			ft_add_count(send, ft_putchar(format[send[0]]));
		else
		{
			send[0]++;
			ret = ft_checker_text(format, &arguments, send);
			send[0] = ret[0];
			send[1] = ret[1];
		}
		send[0]++;
	}
	va_end(arguments);
	if (send[2])
		return (-1);
	return (send[1]);
}
