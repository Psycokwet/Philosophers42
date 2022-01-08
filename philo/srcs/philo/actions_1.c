/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/08 21:04:36 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	clean_first_fork(t_philo_env *p_env)
{
	pthread_mutex_unlock(&p_env->env->forks[p_env->f1]);
}

void	clean_both_fork(t_philo_env *p_env)
{
	pthread_mutex_unlock(&p_env->env->forks[p_env->f1]);
	pthread_mutex_unlock(&p_env->env->forks[p_env->f2]);
}

int	post_action_eat(t_philo_env *p_env)
{
	int	ret;

	p_env->eat_count++;
	ret = my_usleep(p_env->env, p_env->env->params[TIME_TO_EAT],
			p_env->last_time[ACTION_CODE_EAT]
			+ p_env->env->params[TIME_TO_DIE]);
	clean_both_fork(p_env);
	return (ret);
}

void	*philosophe_fun(void *v_philo_env)
{
	t_philo_env	*p_env;

	p_env = (t_philo_env *) v_philo_env;
	while (true)
	{
		if (do_action(p_env, ACTION_CODE_THINK) != EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_THINK, p_env));
		if (do_action_with_clean(p_env, ACTION_CODE_FORK, &take_first_fork,
				&clean_first_fork) != EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_FORK, p_env));
		if (do_action_with_clean(p_env, ACTION_CODE_FORK, &take_second_fork,
				&clean_both_fork) != EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_FORK, p_env));
		if (do_action_with_post(p_env, ACTION_CODE_EAT, &post_action_eat)
			!= EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_EAT, p_env));
		if (p_env->eat_count == p_env->env->params[
				NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT])
			return (quit_philo(EXIT_SUCCESS, p_env));
		if (do_action_with_post(p_env, ACTION_CODE_SLEEP, &post_action_sleep)
			!= EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_SLEEP, p_env));
	}
	return (NULL);
}
