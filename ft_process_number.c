/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:09:24 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/27 16:54:24 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int	ft_process_number(int number)
{
	if (n < 0)
	{
		write(1, '-', 1);
		if (n == -2147483648)
		{
			ft_process_number(2);
			ft_process_number(147483648);
		}
		else
			ft_process_number((n * -1));
	}
	else if (n < 10)
		write(1, &(char)(n + '0'), 1);
	else
	{
		ft_process_number((n / 10));
		write(1, &(char)((n % 10) + '0'), 1);
	}
}
