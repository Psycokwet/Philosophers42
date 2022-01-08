/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/08 16:45:32 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	ft_putstr_str(char *src, char *dst)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	ft_memcpy(dst, src, len_src);
	return (len_src);
}

void	set_state(t_env *env, int id, int state)
{
	((t_philo_env *)env->p_envs)[id].state = state;
}

long	print_action(t_env *env, int id, int action_code)
{
	long	ts;
	char	buffer[1024];
	int		i;

	i = 0;
	ts = get_current_timestamp(env);
	pthread_mutex_lock(&env->mutex_bank[SPEAK_MUT]);
	set_state(env, id, action_code);
	i += ft_putnbr_str(ts, buffer);
	buffer[i++] = ' ';
	i += ft_putnbr_str(id + 1, buffer + i);
	buffer[i++] = ' ';
	i += ft_putstr_str(g_actions_string[action_code], buffer + i);
	buffer[i++] = '\n';
	buffer[i++] = '\0';
	ft_putstr_fd(buffer, STDOUT_FILENO);
	pthread_mutex_unlock(&env->mutex_bank[SPEAK_MUT]);
	return (ts);
}
