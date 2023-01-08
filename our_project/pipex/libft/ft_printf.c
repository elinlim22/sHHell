/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:12 by hyeslim           #+#    #+#             */
/*   Updated: 2022/12/09 22:16:53 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_fs(char c, va_list ap)
{
	int		len;

	len = 0;
	if (c == 'c')
		len += ft_putchar_fd((uintptr_t)va_arg(ap, void *), 1);
	else if (c == 's')
		len += ft_putstr_fd((char *)va_arg(ap, char *), 1);
	else if (c == 'p')
	{
		len += ft_putstr_fd("0x", 1);
		len += print_p(va_arg(ap, void *), 0);
	}
	else if (c == 'd' || c == 'i')
		len += print_di((int)va_arg(ap, int));
	else if (c == 'u')
		len += print_u((unsigned int)va_arg(ap, unsigned int), 1);
	else if (c == 'x' || c == 'X')
	{
		if (c == 'x')
			len += print_x((int)va_arg(ap, int), 0, 0);
		else
			len += print_x((int)va_arg(ap, int), 1, 0);
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '%')
				len += ft_putchar_fd('%', 1);
			else
				len += check_fs(format[i], ap);
		}
		else
			len += ft_putchar_fd(format[i], 1);
		i++;
	}
	return (len);
}
