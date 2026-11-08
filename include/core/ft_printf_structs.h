/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 13:17:25 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/08 13:17:25 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_STRUCTS_H
# define FT_PRINTF_STRUCTS_H

# include "ft_printf_libs.h"
# include "ft_printf_defines.h"

typedef struct s_state
{
	size_t	pos;
	int		count;
	int		error;
}	t_state;

#endif
