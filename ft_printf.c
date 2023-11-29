/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:09:20 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/29 15:12:17 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include <stdio.h>

//void Myprintf(char* format,...);
void	ft_printf(char *formatter, ...);
//char *convert(unsigned int num, int base);

int	main(void)
{
	//Myprintf("WWW.FIRMCODES.COM\n%s\nthrekjshdfrk\n%c\n%x\n%X\n%%\n%d", "HEY", '1', 15, -15,-5);
	ft_printf("WWW.FIRMCODES.COM\n%s\nthrekjshdfrk\n%c\n%x\n%X\n%%\n%d", "HEY", '1', 15, -15,-5);
	return (0);
}

void	ft_printf(char *formatter, ...)
{
	char	*current;
	size_t	index;
	va_list	arguments;

	va_start(arguments, formatter);
	index = 0;
	current = formatter;
	while (current[index] != '\0')
	{
		if (current[index] != '%')
			ft_putchar_fd(current[index], 1);
		else
		{
			index++;
			index = ft_switch(current, index, arguments);
		}
		index++;
	}
	va_end(arguments);
}
/*
void Myprintf(char* format,...) 
{ 
    char *traverse; 
    unsigned int i; 
    char *s; 

    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        while( *traverse != '%' ) 
        { 
			if( *traverse == '\0')
				return;
            putchar(*traverse);
            traverse++; 
        } 
        traverse++; 
        //Module 2: Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);//Fetch char argument
                        putchar(i);
                        break; 

            case 'd' : i = va_arg(arg,int);//Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            putchar('-'); 
                        } 
                        puts(convert(i,10));
                        break; 

            case 's': s = va_arg(arg,char *);//Fetch string
                        puts(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int);//Fetch Hexadecimal rep
                        puts(convert(i,16));
                        break; 
        }
    } 

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 

char	*convert(unsigned int num, int lowercase)
{
	static char	rep[] = "0123456789ABCDEF";
	static char	buffer[50];
    char		*ptr;

    ptr = &buffer[49];
    *ptr = '\0';
    if (num == 0)
		*--ptr = rep[0];
	else
	{
		while (num != 0)
		{
			*--ptr = rep[num % 16];
			num /= 16;
		}
	}
	return (ptr);
}
*/