/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:09:20 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 11:56:22 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Length of a "%%" with flags or a width between, such as "%5%", which glibc
   prints as a single '%'; 0 for anything else. */
static size_t	pf_flagged_percent_length(const char *spec)
{
	size_t	length;

	if (spec[0] != '%')
		return (0);
	length = 1;
	while (spec[length] == '-' || spec[length] == '+' || spec[length] == ' '
		|| spec[length] == '#' || spec[length] == '.'
		|| (spec[length] >= '0' && spec[length] <= '9'))
		length++;
	if (length > 1 && spec[length] == '%')
		return (length + 1);
	return (0);
}

/* Checked before printing so a trailing '%' prints nothing, as in glibc. */
static int	pf_format_is_valid(const char *format)
{
	size_t	pos;

	pos = 0;
	while (format[pos] != '\0')
	{
		if (pf_flagged_percent_length(format + pos) > 0)
			pos += pf_flagged_percent_length(format + pos);
		else if (format[pos] == '%')
		{
			if (format[pos + 1] == '\0')
				return (0);
			pos += 2;
		}
		else
			pos++;
	}
	return (1);
}

static size_t	pf_text_length(const char *text)
{
	size_t	length;

	length = 0;
	while (text[length] != '\0' && text[length] != '%')
		length++;
	return (length);
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
		length = pf_text_length(format + state->pos);
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
