/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/04 11:19:53 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	init_from_params(t_env *env, int argc, char const *argv[])
{
	int i;

	if (argc != PARAM_Q && argc != (PARAM_Q - 1))
	{
		printf("The number of parameters is incorrect, abort\n");
		return (-EXIT_FAILURE);
	}
	i = 0;
	while (i < argc)
	{
		if (parse_value(argv[i], &env->params[i]) != EXIT_SUCCESS || env->params[i] < 1)
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

void *philosophe_fun (void * v_philo_env)
{
	t_philo_env *philo_env;
	int			alive;

	philo_env = (t_philo_env*) v_philo_env;
	alive = true;
	while (alive)
	{
		// print_action(philo_env->env, philo_env->num, 1);

		print_action(philo_env->env, philo_env->num, ACTION_CODE_SLEEP);
		usleep(philo_env->env->params[TIME_TO_SLEEP]);

		print_action(philo_env->env, philo_env->num, ACTION_CODE_THINK);

		try_to_pick_up_fork(philo_env, philo_env->num);
		if (philo_env->eat_count == philo_env->env->params[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT])
		{
			int *res = 0;
			return res;
		}
		// print_action(philo_env->env, philo_env->num, ACTION_CODE_DEAD);
	}
	// sleep(10);
	int *res = 0;
	return res;
}

int	init_forks(t_env *env)
{
	int	i;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->params[NUMBER_OF_PHILOSOPHER]);
	if (!env->forks)
	{
		printf("error malloc\n");
		return (-EXIT_FAILURE);
	}
	// pthread_mutex_t mut;

	i = 0;
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		env->forks[i] = (pthread_mutex_t){};
		pthread_mutex_init(&env->forks[i], NULL);
		i++;
	}

	return (EXIT_SUCCESS);
}

int wrap_philosophers (t_env * env)
{
	t_philo_env	*phils;
	int			i;
	void			*res;

	phils = malloc(sizeof(t_philo_env) * env->params[NUMBER_OF_PHILOSOPHER]);
	if (!phils)
	{
		printf("error malloc\n");
		return (-EXIT_FAILURE);
	}
	i = 0;
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		phils[i].num = i;
		phils[i].last_ate = get_current_timestamp();
		phils[i].eat_count = 0;
		phils[i].env = env;

		if (pthread_create(&phils[i].th, NULL, &philosophe_fun, &phils[i]) != EXIT_SUCCESS)
		{
			printf("error for creating thread :(\n");
			return (-EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		pthread_join(phils[i].th, &res);
		if (res != EXIT_SUCCESS){
			printf("PROBLEME\n");
		}else{

			printf("finished %d\n", i);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char const *argv[])
{
	t_env env;

	env = (t_env){};
	if (init_from_params(&env, argc - 1, &argv[1]) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	printf("ah que cc bob deb\n");
	if (init_forks(&env) != EXIT_SUCCESS)
	{
		printf("error while initializing forks\n");
		return (-EXIT_FAILURE);
	}
	if (wrap_philosophers(&env) != EXIT_SUCCESS)
	{
		printf("error for waiting thread :(\n");
		return (-EXIT_FAILURE);
	}
	printf("The execution have come to an end\n");
}
