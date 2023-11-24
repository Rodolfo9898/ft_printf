/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:12:09 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/23 14:30:04 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t bytes)
{
	unsigned char	*buffer;
	unsigned char	byte_value;
	size_t			i;

	buffer = (unsigned char *)ptr;
	byte_value = (unsigned char)value;
	i = 0;
	while (i < bytes)
	{
		buffer[i] = byte_value;
		i++;
	}
	return (ptr);
}
