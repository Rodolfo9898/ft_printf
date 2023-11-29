/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rperez-t <rperez-t@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:09:20 by rperez-t          #+#    #+#             */
/*   Updated: 2023/11/29 13:17:17 by rperez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

void	ft_printf(char *formatter, ...);

int	main(void)
{
	ft_printf(" WWW.FIRMCODES.COM %sthrekjshdfrk %c\n%i", "HEY", '1', -213678);
	return (0);
}

int	ft_switch(char *str, int index, va_list arguments)
{
	int		return_value;
	char	*pointer_value;

	if (str[index] == 'c')
	{
		return_value = va_arg(arguments, int);
		ft_putchar_fd(return_value, 1);
	}
	else if (str[index] == 's')
	{
		pointer_value = va_arg(arguments, char *);
		ft_putstr_fd(pointer_value, 1);
	}
	else if (str[index] == 'i' || str[index] == 'd')
	{
		return_value = va_arg(arguments, int);
		ft_putnbr_fd(return_value, 1);
	}
	return (index);
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

char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}*/
