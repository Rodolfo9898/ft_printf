/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:47:13 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/27 14:41:14 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

void	*ft_memset(void *ptr, int value, size_t bytes);
void	ft_bzero(void *ptr, size_t bytes);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_process_char(char c);
int		ft_process_string(char *str);

#endif
