/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 08:47:13 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/24 17:26:52 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_options
{
	int	sharp;
	int	space;
	int	plus;
	int	minimum;
	int	minus;
	int	dot;
	int	precision;
	int	offset;
	int	zero;
	int	zero_offset;
}		t_options;

void	*ft_memset(void *ptr, int value, size_t bytes);
void	ft_bzero(void *ptr, size_t bytes);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_process_char(char c);
int		ft_print_char(char c, t_options options);

#endif
