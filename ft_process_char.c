/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:28:34 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/24 17:19:41 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int	ft_process_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_char(char c, t_options options)
{
	int	i;

	i = 0;
	while (i + 1 < options.minimum)
		i += ft_process_char(' ');
	i += ft_process_char(c);
	while (i < options.offset)
		i += ft_process_char(' ');
	return (i);
}
