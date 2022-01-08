/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/08 15:17:34 by scarboni         ###   ########.fr       */
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

int	post_action_sleep(t_philo_env *p_env)
{
	return (my_usleep(p_env->env, p_env->env->params[TIME_TO_SLEEP],
			p_env->last_time[ACTION_CODE_EAT]
			+ p_env->env->params[TIME_TO_DIE]));
}

int	pre_action_eat(t_philo_env *p_env)
{
	return (try_to_pick_up_fork(p_env, p_env->num));
}

int	take_first_fork(t_philo_env *p_env)
{
	pthread_mutex_lock(&p_env->env->forks[p_env->f1]);
	return (EXIT_SUCCESS);
}

int	take_second_fork(t_philo_env *p_env)
{
	if (p_env->env->params[NUMBER_OF_PHILOSOPHER] == 1)
	{
		my_usleep(p_env->env, p_env->env->params[TIME_TO_DIE]
			- get_current_timestamp(p_env->env),
			p_env->env->params[TIME_TO_DIE]);
		return (-EXIT_FAILURE);
	}
	pthread_mutex_lock(&p_env->env->forks[p_env->f2]);
	return (EXIT_SUCCESS);
}

void	clean_first_fork(t_philo_env *p_env)
{
	pthread_mutex_unlock(&p_env->env->forks[p_env->f1]);
}

void	clean_both_fork(t_philo_env *p_env)
{
	pthread_mutex_unlock(&p_env->env->forks[p_env->f1]);
	pthread_mutex_unlock(&p_env->env->forks[p_env->f2]);
}

int	post_action_eat(t_philo_env *p_env)
{
	int	ret;

	p_env->eat_count++;
	ret = my_usleep(p_env->env, p_env->env->params[TIME_TO_EAT],
			p_env->last_time[ACTION_CODE_EAT]
			+ p_env->env->params[TIME_TO_DIE]);
	clean_both_fork(p_env);
	return (ret);
}

void	*philosophe_fun(void *v_philo_env)
{
	t_philo_env	*p_env;

	p_env = (t_philo_env *) v_philo_env;
	ft_putstr_fd("\r", STDOUT_FILENO);
	usleep((p_env->num * 12634556) % 1000);
	while (true)
	{
		if (do_action(p_env, ACTION_CODE_THINK) != EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_THINK, p_env));
		if (do_action_with_clean(p_env, ACTION_CODE_FORK, &take_first_fork,
				&clean_first_fork) != EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_FORK, p_env));
		if (do_action_with_clean(p_env, ACTION_CODE_FORK, &take_second_fork,
				&clean_both_fork) != EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_FORK, p_env));
		if (do_action_with_post(p_env, ACTION_CODE_EAT, &post_action_eat)
			!= EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_EAT, p_env));
		if (p_env->eat_count == p_env->env->params[
				NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT])
			return (quit_philo(EXIT_SUCCESS, p_env));
		if (do_action_with_post(p_env, ACTION_CODE_SLEEP, &post_action_sleep)
			!= EXIT_SUCCESS)
			return (quit_philo(-ACTION_CODE_SLEEP, p_env));
	}
	return (NULL);
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
	return (((t_philo_env *)env->p_envs)[i].last_time[ACTION_CODE_EAT]);
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

int	get_right_fork_id(t_env *env, int id)
{
	if (id == 0)
		return (env->params[NUMBER_OF_PHILOSOPHER] - 1);
	return (id - 1);
}

int	start_philo(t_philo_env *phils, int i, t_env *env)
{
	int			left;
	int			right;

	left = get_left_fork_id(i);
	right = get_right_fork_id(env, i);
	phils[i].num = i;
	phils[i].last_time[ACTION_CODE_EAT] = 0;
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
	if (pthread_create(&phils[i].th, NULL, &philosophe_fun, &phils[i])
		!= EXIT_SUCCESS)
	{
		printf("error for creating thread :(\n");
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	wrap_philosophers(t_env *env)
{
	t_philo_env	*phils;
	int			i;
	void		*res;

	phils = (t_philo_env *)malloc(sizeof(t_philo_env)
			* env->params[NUMBER_OF_PHILOSOPHER]);
	env->p_envs = phils;
	if (!phils)
	{
		printf("error malloc\n");
		return (-EXIT_FAILURE);
	}
	i = 0;
	env->started_at = get_base_timestamp();
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		start_philo(phils, i, env);
		i += 2;
	}
	i = 1;
	// usleep(100);
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		start_philo(phils, i, env);
		i += 2;
	}
	i = 0;
	while (i < env->params[NUMBER_OF_PHILOSOPHER])
	{
		pthread_join(phils[i].th, &res);
		if (res != EXIT_SUCCESS)
			printf("PROBLEME\n");
		else
			printf("finished %d\n", i);
		i++;
	}
	// i = 0;
	// while (i < env->params[NUMBER_OF_PHILOSOPHER])
	// {
	// 	if (pthread_detach(phils[i].th))
	// 		printf("thread detachment has failed\n");
	// 	i++;
	// }
	// free(phils);
	// free(env->forks);
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
