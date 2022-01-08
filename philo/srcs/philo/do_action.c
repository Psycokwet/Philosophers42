/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/08 16:31:32 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	set_stop(t_philo_env *p_env)
{
	pthread_mutex_lock(&p_env->env->mutex_bank[DEATH_MUT]);
	if (!p_env->env->stop)
	{
		p_env->env->stop = true;
		print_action(p_env->env, p_env->num, ACTION_CODE_DEAD);
	}
	pthread_mutex_unlock(&p_env->env->mutex_bank[DEATH_MUT]);
	return (-EXIT_FAILURE);
}

int	check_stop(t_philo_env *p_env)
{
	pthread_mutex_lock(&p_env->env->mutex_bank[DEATH_MUT]);
	if (p_env->env->stop == true)
	{
		pthread_mutex_unlock(&p_env->env->mutex_bank[DEATH_MUT]);
		return (true);
	}
	pthread_mutex_unlock(&p_env->env->mutex_bank[DEATH_MUT]);
	return (false);
}

int	do_action(t_philo_env *p_env, int action_code)
{
	if (p_env->last_time[ACTION_CODE_EAT] + p_env->env->params[TIME_TO_DIE]
		< get_current_timestamp(p_env->env))
	{
		return (set_stop(p_env));
	}
	pthread_mutex_lock(&p_env->env->mutex_bank[DEATH_MUT]);
	if (p_env->env->stop == true)
	{
		pthread_mutex_unlock(&p_env->env->mutex_bank[DEATH_MUT]);
		return (-EXIT_FAILURE);
	}
	p_env->last_time[action_code] = print_action(p_env->env, p_env->num,
			action_code);
	pthread_mutex_unlock(&p_env->env->mutex_bank[DEATH_MUT]);
	return (EXIT_SUCCESS);
}

int	do_action_with_clean(t_philo_env *p_env, int action_code,
int (*pre_action)(t_philo_env*), void (*clean_if_death_action)(t_philo_env*))
{
	if (pre_action(p_env) != EXIT_SUCCESS)
	{
		clean_if_death_action(p_env);
		return (set_stop(p_env));
	}
	if (do_action(p_env, action_code) != EXIT_SUCCESS)
	{
		clean_if_death_action(p_env);
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	do_action_with_post(t_philo_env *p_env, int action_code,
int (*post_action)(t_philo_env*))
{
	if (do_action(p_env, action_code) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	if (post_action(p_env) != EXIT_SUCCESS)
		return (set_stop(p_env));
	return (EXIT_SUCCESS);
}
