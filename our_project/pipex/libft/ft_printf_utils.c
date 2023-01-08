/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:50:41 by hyeslim           #+#    #+#             */
/*   Updated: 2022/11/18 19:54:49 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_p(void *pt, int flag)
{
	unsigned long	ptr;
	static int		res;

	ptr = (unsigned long)pt;
	res = 0;
	if (!ptr && !flag)
	{
		res += ft_putchar_fd('0', 1);
		return (res);
	}
	else if (ptr > 0)
	{
		flag = 1;
		print_p((void *)(ptr / 16), flag);
		res += ft_putchar_fd("0123456789abcdef"[ptr % 16], 1);
	}
	return (res);
}

int	print_di(int i)
{
	return (ft_putnbr_fd(i, 1));
}

int	print_u(unsigned int i, int fd)
{
	static int	len;
	char		c;

	len = 0;
	if (i < 10)
	{
		c = i + '0';
		len += ft_putchar_fd(c, fd);
	}
	else
	{
		print_u(i / 10, fd);
		c = i % 10 + '0';
		len += ft_putchar_fd(c, fd);
	}
	return (len);
}

int	print_x(unsigned int i, int lu, int flag)
{
	static int	res;

	res = 0;
	if (!i && !flag)
		return (res += ft_putchar_fd('0', 1));
	else if (i > 0)
	{
		flag = 1;
		print_x(i / 16, lu, flag);
		if (!lu)
			res += ft_putchar_fd("0123456789abcdef"[i % 16], 1);
		else
			res += ft_putchar_fd("0123456789ABCDEF"[i % 16], 1);
	}
	return (res);
}
