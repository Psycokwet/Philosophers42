/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/11/19 19:59:59 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

long	print_action(t_env* env, int id, int action_code)
{
	long ts;

	ts = get_current_timestamp(env);
	pthread_mutex_lock(&env->mutex_bank[SPEAK_MUT]);
	set_state(env, id, action_code);
	ft_putnbr_fd(ts, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putnbr_fd(id + 1, STDOUT_FILENO);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(g_actions_string[action_code], STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	pthread_mutex_unlock(&env->mutex_bank[SPEAK_MUT]);
	return (ts);
}
