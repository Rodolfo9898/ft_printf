/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:09:20 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 10:45:24 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_state	state;
	va_list	arguments;

	if (!format)
		return (-1);
	va_start(arguments, format);
	state.pos = 0;
	state.count = 0;
	state.error = 0;
	while (!state.error && format[state.pos] != '\0')
	{
		if (format[state.pos] == '%')
		{
			state.pos++;
			pf_dispatch(format, &arguments, &state);
		}
		else
			pf_add_count(&state, pf_putchar(format[state.pos]));
		state.pos++;
	}
	va_end(arguments);
	if (state.error)
		return (-1);
	return (state.count);
}
