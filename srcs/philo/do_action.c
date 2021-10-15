/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/15 08:26:42 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	do_action(t_philo_env* p_env, int action_code, void (*pre_action)(t_philo_env*), void (*post_action)(t_philo_env*))
{
	if (pre_action)
		pre_action(p_env);
	pthread_mutex_lock(&p_env->env->mutex_bank[DEATH_MUT]);
	if (p_env->env->stop == true)
	{
		pthread_mutex_unlock(&p_env->env->mutex_bank[DEATH_MUT]);
		return (EXIT_FAILURE);
	}
	if (p_env->last_ate + p_env->env->params[TIME_TO_DIE] < get_current_timestamp())
	{
		p_env->env->stop = true;
		pthread_mutex_unlock(&p_env->env->mutex_bank[DEATH_MUT]);
		print_action(p_env->env, p_env->num, ACTION_CODE_DEAD);
		return (EXIT_FAILURE);
	}
	print_action(p_env->env, p_env->num, action_code);
	pthread_mutex_unlock(&p_env->env->mutex_bank[DEATH_MUT]);
	if (post_action)
		post_action(p_env);
	return (EXIT_SUCCESS);
}
