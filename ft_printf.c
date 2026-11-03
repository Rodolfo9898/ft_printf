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
	t_state	state;
	va_list	arguments;

	va_start(arguments, format);
	state.pos = 0;
	state.count = 0;
	state.error = 0;
	while (!state.error && format[state.pos] != '\0')
	{
		if (format[state.pos] == '%')
		{
			state.pos++;
			ft_dispatch(format, &arguments, &state);
		}
		else
			ft_add_count(&state, ft_putchar(format[state.pos]));
		state.pos++;
	}
	va_end(arguments);
	if (state.error)
		return (-1);
	return (state.count);
}
