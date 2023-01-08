/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:37:30 by hyeslim           #+#    #+#             */
/*   Updated: 2022/11/09 19:39:42 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *i, int *j)
{
	int	temp;

	temp = *i;
	*i = *j;
	*j = temp;
}

void	ft_sort(int *tab, int size)
{
	int	i;
	int	circle;

	i = 0;
	circle = 0;
	while (circle + 1 < size)
	{
		while (i + 1 < size)
		{
			if (tab[i] > tab[i + 1])
			{
				ft_swap(tab + i, tab + i + 1);
			}
			i++;
		}
		circle++;
		i = 0;
	}
}
