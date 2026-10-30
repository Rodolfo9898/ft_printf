/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:47:13 by rperez-t          #+#    #+#             */
/*   Updated: 2026/10/30 16:20:18 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

int		ft_putchar(int c);
int		ft_putstr(char *s);
char	*ft_itoa(long n);
int		ft_putnbr(int n);
int		ft_putunbr(unsigned int n);
char	*ft_make_hex(unsigned long number, int lowercase);
int		ft_putptr(uintptr_t p);
void	ft_add_count(int *send, int written);
int		*ft_checker_text(const char *str, va_list *arguments, int *send);
int		ft_printf(const char *format, ...);

#endif
