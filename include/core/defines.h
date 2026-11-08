/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 13:17:25 by rperez-t          #+#    #+#             */
/*   Updated: 2026/11/08 13:17:25 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* The libc printf prints a NULL %p as "0x0" on macOS and "(nil)" on Linux. */
# ifdef __APPLE__
#  define NULL_PTR_STR "0x0"
# else
#  define NULL_PTR_STR "(nil)"
# endif

# define DECIMAL "0123456789"
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"

#endif
