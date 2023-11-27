/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:09:24 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/27 18:02:18 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

void	ft_process_number(int number)
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
			ft_process_number((number * -1));
	}
	else if (number < 10)
		write(1, &(char)(number + '0'), 1);
	else
	{
		ft_process_number((number / 10));
		write(1, &(char)((number % 10) + '0'), 1);
	}
}
