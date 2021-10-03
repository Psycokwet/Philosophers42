/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/03 10:54:26 by scarboni         ###   ########.fr       */
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

int	try_to_pick_up_fork(t_env *env, int id)
{
	int	left_id;
	int	right_id;

	if (env->params[NUMBER_OF_PHILOSOPHER] == 1)
	{
		printf("Can't take up two fork, there is only one\n");
		return (-EXIT_FAILURE);
	}
	left_id = get_left_fork_id(id);
	right_id = get_left_right_id(env, id);
	printf("ID %d has left %d and right %d\n", id, left_id, right_id);
	return (EXIT_SUCCESS);
}