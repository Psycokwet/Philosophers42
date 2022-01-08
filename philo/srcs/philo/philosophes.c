/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/08 17:55:32 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	get_left_fork_id(int id)
{
	return (id);
}

int	get_right_fork_id(t_env *env, int id)
{
	if (id == 0)
		return (env->params[NUMBER_OF_PHILOSOPHER] - 1);
	return (id - 1);
}

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

int	wrap_philosophers(t_env *env)
{
	t_philo_env	*phils;
	int			i;
	void		*res;

	phils = (t_philo_env *)malloc(sizeof(t_philo_env)
			* env->params[NUMBER_OF_PHILOSOPHER]);
	env->p_envs = phils;
	if (!phils)
	{
		printf("error malloc\n");
		return (-EXIT_FAILURE);
	}
	i = 0;
	env->started_at = get_base_timestamp();
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		start_philo(phils, i, env);
		i += 2;
	}
	i = 1;
	// usleep(100);
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		start_philo(phils, i, env);
		i += 2;
	}
	i = 0;
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		pthread_join(phils[i].th, &res);
		if (res != EXIT_SUCCESS)
			printf("PROBLEME\n");
		else
			printf("finished %d\n", i);
		i++;
	}
	// i = 0;
	// while (i < env->params[NUMBER_OF_PHILOSOPHER])
	// {
	// 	if (pthread_detach(phils[i].th))
	// 		printf("thread detachment has failed\n");
	// 	i++;
	// }
	// free(phils);
	// free(env->forks);
	return (EXIT_SUCCESS);
}
