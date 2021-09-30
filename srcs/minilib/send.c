/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/27 22:55:23 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	send_zero(int server_pid)
{
	return (kill(server_pid, SIGUSR2));
}

int	send_one(int server_pid)
{
	return (kill(server_pid, SIGUSR1));
}

int	send_null(int server_pid)
{
	int	i;

	i = 0;
	while (i < BYTE_SIZE)
	{
		if (send_zero(server_pid) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	send_letter(int server_pid, char letter)
{
	int	i;
	int	ret;

	i = 0;
	while (i < BYTE_SIZE)
	{
		if ((letter >> i) & 1)
			ret = send_one(server_pid);
		else
			ret = send_zero(server_pid);
		if (ret != EXIT_SUCCESS)
			return (ret);
		i++;
	}
	return (EXIT_SUCCESS);
}
