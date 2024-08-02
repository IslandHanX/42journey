/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:38:10 by xhan              #+#    #+#             */
/*   Updated: 2024/07/02 20:58:11 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_switch(char format, va_list args)
{
	if (format == '%')
		return (write(1, "%", 1));
	else if (format == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		return (1);
	}
	else if (format == 's')
		return (prt_str(va_arg(args, char *)));
	else if (format == 'p')
		return (prt_ptr(va_arg(args, void *)));
	else if (format == 'd' || format == 'i')
		return (prt_int(va_arg(args, int)));
	else if (format == 'u')
		return (prt_unsigned(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (prt_hexa(va_arg(args, unsigned int), false));
	else if (format == 'X')
		return (prt_hexa(va_arg(args, unsigned int), true));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	if (!format)
		return (0);
	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += ft_switch(format[i], args);
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
