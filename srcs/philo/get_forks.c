/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/04 11:10:13 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	get_left_fork_id(int id)
{
	return (id);
}

int	get_left_right_id(t_env *env, int id)
{
	if (id == 0)
		return (env->params[NUMBER_OF_PHILOSOPHER] - 1);
	return (id - 1);
}

int	try_to_pick_up_fork(t_philo_env *p_env, int id)
{
	int	left_id;
	int	right_id;

	if (p_env->env->params[NUMBER_OF_PHILOSOPHER] == 1)
	{
		printf("Can't take up two fork, there is only one\n");
		return (-EXIT_FAILURE);
	}
	left_id = get_left_fork_id(id);
	right_id = get_left_right_id(p_env->env, id);

	pthread_mutex_lock(&p_env->env->table);
	pthread_mutex_lock(&p_env->env->forks[left_id]);
	print_action(p_env->env, p_env->num, ACTION_CODE_FORK);
	pthread_mutex_lock(&p_env->env->forks[right_id]);
	print_action(p_env->env, p_env->num, ACTION_CODE_FORK);
	pthread_mutex_unlock(&p_env->env->table);

	printf("ID %d has left %d and right %d\n", id, left_id, right_id);

	p_env->last_ate = print_action(p_env->env, p_env->num, ACTION_CODE_EAT);
	p_env->eat_count++;
	usleep(p_env->env->params[TIME_TO_EAT]);

	pthread_mutex_unlock(&p_env->env->forks[left_id]);
	pthread_mutex_unlock(&p_env->env->forks[right_id]);
	return (EXIT_SUCCESS);
}