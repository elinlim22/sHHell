/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:04:23 by hyeslim           #+#    #+#             */
/*   Updated: 2022/09/25 18:17:49 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char		c;
	static int	len;

	len = 0;
	if (n == -2147483648)
		len += ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		ft_putnbr_fd(n, fd);
		len++;
	}
	else if (n < 10)
	{
		c = n + '0';
		len += ft_putchar_fd(c, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		c = n % 10 + '0';
		len += ft_putchar_fd(c, fd);
	}
	return (len);
}
