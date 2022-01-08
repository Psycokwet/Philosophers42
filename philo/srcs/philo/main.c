/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/08 16:43:25 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	init_from_params(t_env *env, int argc, char const *argv[])
{
	int	i;

	if (argc != PARAM_Q && argc != (PARAM_Q - 1))
	{
		printf("The number of parameters is incorrect, abort\n");
		return (-EXIT_FAILURE);
	}
	i = 0;
	while (i < argc)
	{
		if (parse_value(argv[i], &env->params[i]) != EXIT_SUCCESS
			|| env->params[i] < 1)
		{
			printf("Error while parsing parameters, abort\n");
			return (-EXIT_FAILURE);
		}
		i++;
	}
	if (i < PARAM_Q)
		env->params[i] = -1;
	return (EXIT_SUCCESS);
}

int	init_mutexes(pthread_mutex_t **list, int max)
{
	int	i;

	*list = malloc(sizeof(pthread_mutex_t) * max);
	if (!(*list))
	{
		printf("error malloc\n");
		return (-EXIT_FAILURE);
	}
	i = 0;
	while (i < max)
	{
		(*list)[i] = (pthread_mutex_t){};
		pthread_mutex_init(&(*list)[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char const *argv[])
{
	t_env	env;

	env = (t_env){};
	ft_putstr_fd("\r", STDOUT_FILENO);
	if (init_from_params(&env, argc - 1, &argv[1]) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	if (init_mutexes(&env.forks, env.params[NUMBER_OF_PHILOSOPHER])
		!= EXIT_SUCCESS)
		return (quit(&env, "error while initializing forks", -EXIT_FAILURE));
	if (init_mutexes(&env.mutex_bank, MUTEX_G_Q) != EXIT_SUCCESS)
		return (quit(&env, "error while initializing global mutexes",
				-EXIT_FAILURE));
	if (wrap_philosophers(&env) != EXIT_SUCCESS)
		return (quit(&env, "error for waiting thread", -EXIT_FAILURE));
	return (quit(&env, "The execution have come to an end", EXIT_SUCCESS));
}
