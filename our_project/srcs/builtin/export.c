/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:04:02 by huipark           #+#    #+#             */
/*   Updated: 2023/01/08 23:35:21 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_export(t_env env)
{
	int	return_value;

	while (env.next)
	{
		env = (*env.next);

	}
}
/*
	strcmp로 검사
	모두 검사하고 모든 리턴값이 음수일경우 피봇str이 가장 적은 ascil 문자를 가진 str
	양수가 있는경우 가장 큰 값을 가진 str이 가장 적은 ascil 문자를 가진 str
*/
