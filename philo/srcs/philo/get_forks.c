/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/11 11:42:33 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	try_to_pick_up_fork(t_philo_env *p_env)
{
	if (p_env->env->params[NUMBER_OF_PHILOSOPHER] == 1)
	{
		pthread_mutex_lock(&p_env->env->forks[0]);
		print_action(p_env->env, p_env->num, ACTION_CODE_FORK);
		printf("Can't take up two fork, there is only one\n");
		return (-EXIT_FAILURE);
	}
	pthread_mutex_lock(&p_env->env->forks[p_env->f1]);
	print_action(p_env->env, p_env->num, ACTION_CODE_FORK);
	pthread_mutex_lock(&p_env->env->forks[p_env->f2]);
	print_action(p_env->env, p_env->num, ACTION_CODE_FORK);
	return (EXIT_SUCCESS);
}
