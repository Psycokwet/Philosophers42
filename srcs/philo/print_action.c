/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/07 15:07:00 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

long	print_action(t_env* env, int id, int action_code)
{
	long ts;

	ts = get_current_timestamp();
	pthread_mutex_lock(&env->speak);
	ft_putnbr_fd(ts, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putnbr_fd(id + 1, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(g_actions_string[action_code], STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	pthread_mutex_unlock(&env->speak);
	return (ts);
}
