/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/10/13 19:36:07 by scarboni         ###   ########.fr       */
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


int	get_last_ate(t_env *env, int i)
{
	return (((t_philo_env *)env->p_envs)[i].last_ate);
}

int	get_state(t_env *env, int i)
{
	return (((t_philo_env *)env->p_envs)->state);
}

void	set_state(t_env *env, int i, int state)
{
	((t_philo_env *)env->p_envs)->state = state;
}


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


int wrap_philosophers (t_env * env)
{
	t_philo_env	*phils;
	int			i;
	void		*res;
	int			left;
	int			right;

	phils = (t_philo_env *)malloc(sizeof(t_philo_env) * env->params[NUMBER_OF_PHILOSOPHER]);
	env->p_envs = phils;
	if (!phils)
	{
		printf("error malloc\n");
		return (-EXIT_FAILURE);
	}
	i = 0;
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		left = get_left_fork_id(i);
		right = get_left_right_id(env, i);
		phils[i].num = i;
		phils[i].last_ate = get_current_timestamp();
		phils[i].eat_count = 0;
		phils[i].env = env;
		if (i % 2 == 1)
		{
			phils[i].f1 = left;
			phils[i].f2 = right;
		}
		else
		{
			phils[i].f1 = right;
			phils[i].f2 = left;
		}
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
	free(phils);
	free(env->forks);
	return (EXIT_SUCCESS);
}

int	main(int argc, char const *argv[])
{
	t_env env;

	env = (t_env){};
	if (init_from_params(&env, argc - 1, &argv[1]) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	if (init_mutexes(&env.forks, env.params[NUMBER_OF_PHILOSOPHER]) != EXIT_SUCCESS)
		return (quit(&env, "error while initializing forks", -EXIT_FAILURE));
	if (init_mutexes(&env.mutex_bank, MUTEX_G_Q) != EXIT_SUCCESS)
		return (quit(&env, "error while initializing global mutexes", -EXIT_FAILURE));
	if (wrap_philosophers(&env) != EXIT_SUCCESS)
		return (quit(&env, "error for waiting thread", -EXIT_FAILURE));
	return (quit(&env, "The execution have come to an end", EXIT_SUCCESS));	
}
