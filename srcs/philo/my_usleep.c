/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/11/15 21:36:48 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	my_usleep(int delay_in_millis, int max_time_before_death)
{
	long int	start_time;
	long int	current_time;

	start_time = get_current_timestamp();
	current_time = get_current_timestamp();
	while ((current_time - start_time) < delay_in_millis)
	{
		if(max_time_before_death != CANT_DIE && (current_time - start_time) > max_time_before_death)
			return (EXIT_FAILURE);
		usleep(100);
		current_time = get_current_timestamp();
	}
	return (EXIT_SUCCESS);
}
