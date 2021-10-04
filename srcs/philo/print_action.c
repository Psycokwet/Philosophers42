/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/04 09:06:18 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	print_action(t_env* env, int id, int action_code)
{
	struct timeval tv;
	struct timezone tz;

	pthread_mutex_lock(&env->speak);
	gettimeofday(&tv, &tz);
	ft_putnbr_fd((tv.tv_sec * 1000) + (tv.tv_usec / 1000), STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putnbr_fd(id + 1, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(g_actions_string[action_code], STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	pthread_mutex_unlock(&env->speak);
}
