/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:21:46 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/24 16:22:00 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;
	size_t	limit;

	if (nmemb == 0 || size == 0)
		return (NULL);
	limit = nmemb * size;
	buffer = malloc(limit);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, size * nmemb);
	return (buffer);
}
