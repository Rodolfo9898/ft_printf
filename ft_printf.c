/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:09:20 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 11:41:28 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Checked before printing so a trailing '%' prints nothing, as in glibc. */
static int	pf_format_is_valid(const char *format)
{
	size_t	pos;

	pos = 0;
	while (format[pos] != '\0')
	{
		if (format[pos] == '%')
		{
			if (format[pos + 1] == '\0')
				return (0);
			pos++;
		}
		pos++;
	}
	return (1);
}

int	ft_printf(const char *format, ...)
{
	t_state	state;
	va_list	arguments;

	if (!format || !pf_format_is_valid(format))
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
