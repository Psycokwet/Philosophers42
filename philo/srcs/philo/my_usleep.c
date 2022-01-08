/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/08 15:04:54 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	my_usleep(t_env *env, int delay_in_millis, int max_time_before_death)
{
	long int	start_time;
	long int	current_time;

	start_time = get_current_timestamp(env);
	current_time = get_current_timestamp(env);
	while ((current_time - start_time) < delay_in_millis)
	{
		if (current_time >= max_time_before_death)
			return (EXIT_FAILURE);
		usleep(delay_in_millis * 1);
		current_time = get_current_timestamp(env);
	}
	return (EXIT_SUCCESS);
}
