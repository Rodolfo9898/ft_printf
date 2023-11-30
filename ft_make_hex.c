/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:45:09 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/30 12:40:15 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_make_hex(unsigned long num, int lowercase)
{
	static char	rep[] = "0123456789ABCDEF";
	static char	buffer[100];
	char		*ptr;

	ptr = &buffer[99];
	*ptr = '\0';
	if (num == 0)
		*--ptr = rep[0];
	else
	{
		while (num != 0)
		{
			if (lowercase && 9 < num % 16)
				*--ptr = rep[num % 16] + 32;
			else
				*--ptr = rep[num % 16];
			num /= 16;
		}
	}
	return (ptr);
}
