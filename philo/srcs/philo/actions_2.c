/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/11 12:06:37 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	post_action_sleep(t_philo_env *p_env)
{
	return (my_usleep(p_env->env, p_env->env->params[TIME_TO_SLEEP],
			p_env->last_time[ACTION_CODE_EAT]
			+ p_env->env->params[TIME_TO_DIE]));
}

int	pre_action_eat(t_philo_env *p_env)
{
	return (try_to_pick_up_fork(p_env));
}

int	take_first_fork(t_philo_env *p_env)
{
	pthread_mutex_lock(&p_env->env->forks[p_env->f1]);
	return (EXIT_SUCCESS);
}

int	take_second_fork(t_philo_env *p_env)
{
	if (p_env->env->params[NUMBER_OF_PHILOSOPHER] == 1)
	{
		my_usleep(p_env->env, p_env->env->params[TIME_TO_DIE]
			- get_current_timestamp(p_env->env),
			p_env->env->params[TIME_TO_DIE]);
		return (-EXIT_FAILURE);
	}
	pthread_mutex_lock(&p_env->env->forks[p_env->f2]);
	return (EXIT_SUCCESS);
}
