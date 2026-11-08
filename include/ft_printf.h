/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:47:13 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/03 11:56:22 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "core/ft_printf_structs.h"

/* From ft_printf.c */
int		ft_printf(const char *format, ...);

/* From print/ft_format.c */
int		pf_format_is_valid(const char *format);
void	pf_print_segment(const char *format, va_list *arguments,
			t_state *state);

/* From print/ft_dispatch.c */
int		pf_print_conversion(char specifier, va_list *arguments);

/* From print/ft_print_utils.c */
int		pf_write_all(const char *buffer, size_t length);
int		pf_putchar(int c);
int		pf_putnbr_base(uintmax_t number, const char *base);

#endif
