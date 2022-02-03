/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/11 11:49:43 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	start_philo(t_philo_env *phils, int i, t_env *env)
{
	int			left;
	int			right;

	left = get_left_fork_id(i);
	right = get_right_fork_id(env, i);
	phils[i] = (t_philo_env){env, right, left, i, -1, 0, 0, {0}};
	if (i % 2 == 1)
	{
		phils[i].f1 = left;
		phils[i].f2 = right;
	}
	if (pthread_create(&phils[i].th, NULL, &philosophe_fun, &phils[i])
		!= EXIT_SUCCESS)
	{
		printf("error for creating thread :(\n");
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	start_all_philos(t_philo_env *phils, t_env *env)
{
	int	i;

	i = 0;
	env->started_at = get_base_timestamp();
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		if (start_philo(phils, i, env) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
		i += 2;
	}
	i = 1;
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		if (start_philo(phils, i, env) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
		i += 2;
	}
	return (EXIT_SUCCESS);
}

int	cleanup_philosophers(int error, t_philo_env *phils, t_env *env)
{
	int			i;
	void		*res;

	i = 0;
	if (error == -EXIT_FAILURE)
	{
		while (i < env->params[NUMBER_OF_PHILOSOPHER])
		{
			if (phils[i].th)
				pthread_detach(phils[i].th);
			i++;
		}
	}
	else
	{
		while (i < env->params[NUMBER_OF_PHILOSOPHER])
		{
			pthread_join(phils[i].th, &res);
			i++;
		}
	}
	return (error);
}

int	wrap_philosophers(t_env *env)
{
	t_philo_env	*phils;

	phils = (t_philo_env *)malloc(sizeof(t_philo_env)
			* env->params[NUMBER_OF_PHILOSOPHER]);
	env->p_envs = phils;
	if (!phils)
	{
		printf("error malloc\n");
		return (-EXIT_FAILURE);
	}
	return (cleanup_philosophers(start_all_philos(phils, env), phils, env));
}
