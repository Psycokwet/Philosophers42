/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/13 19:03:05 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	do_action(t_philo_env* p_env, int action_code, void *(*action)(t_philo_env*))
{
	if (p_env->env->stop == true)
		return (EXIT_FAILURE);

	print_action(p_env->env, p_env->num, action_code);
	return (EXIT_SUCCESS);
}
