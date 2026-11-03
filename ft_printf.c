/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:09:20 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 14:59:16 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Number of flag or width characters right after the '%' at spec[0], such as
   2 for "%-5d". */
static size_t	pf_flags_length(const char *spec)
{
	size_t	length;

	length = 0;
	while (spec[length + 1] == '-' || spec[length + 1] == '+'
		|| spec[length + 1] == ' ' || spec[length + 1] == '#'
		|| spec[length + 1] == '.'
		|| (spec[length + 1] >= '0' && spec[length + 1] <= '9'))
		length++;
	return (length);
}

/* Length of a "%%" with flags or a width between, such as "%5%", which glibc
   prints as a single '%'; 0 for anything else. */
static size_t	pf_flagged_percent_length(const char *spec)
{
	size_t	flags;

	if (spec[0] != '%')
		return (0);
	flags = pf_flags_length(spec);
	if (flags > 0 && spec[flags + 1] == '%')
		return (flags + 2);
	return (0);
}

/* Checked before printing so a format ending in a '%', alone or followed only
   by flags or a width ("abc%", "abc%5"), prints nothing, as in glibc. */
static int	pf_format_is_valid(const char *format)
{
	size_t	pos;
	size_t	length;

	pos = 0;
	while (format[pos] != '\0')
	{
		length = pf_flagged_percent_length(format + pos);
		if (length > 0)
			pos += length;
		else if (format[pos] == '%')
		{
			if (format[pos + pf_flags_length(format + pos) + 1] == '\0')
				return (0);
			pos += 2;
		}
		else
			pos++;
	}
	return (1);
}

/* Prints one conversion, or all the text up to the next '%' in one write.
   The format was validated, so a '%' is never followed by the '\0'. */
static void	pf_print_segment(const char *format, va_list *arguments,
		t_state *state)
{
	size_t	length;

	length = pf_flagged_percent_length(format + state->pos);
	if (length > 0)
		pf_add_count(state, pf_putchar('%'));
	else if (format[state->pos] == '%')
	{
		pf_add_count(state,
			pf_print_conversion(format[state->pos + 1], arguments));
		length = 2;
	}
	else
	{
		while (format[state->pos + length] != '\0'
			&& format[state->pos + length] != '%')
			length++;
		pf_add_count(state, pf_write_all(format + state->pos, length));
	}
	state->pos += length;
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
		pf_print_segment(format, &arguments, &state);
	va_end(arguments);
	if (state.error)
		return (-1);
	return (state.count);
}
