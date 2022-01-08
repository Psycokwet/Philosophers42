/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/05/06 09:33:00 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stddef.h>
# include <stdbool.h>
# include <string.h>

# include <stdio.h>

// printf
# include <stdlib.h>

// malloc
// free
# include <unistd.h>

// ssize_t write(int fd, const void *buf, size_t count);
# include <unistd.h>

//int usleep(useconds_t usec);
# include <sys/time.h>

//int gettimeofday(struct timeval *tv, struct timezone *tz);
# include <pthread.h>

//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//			void *(*start_routine) (void *), void *arg);
//int pthread_detach(pthread_t thread);
//int pthread_join(pthread_t thread, void **retval);
// pthread_mutex_init
// pthread_mutex_destroy
// pthread_mutex_lock
// pthread_mutex_unlock
# define PARAM_Q 5

# define ACTION_TEXT_FORK	"\033[0;33mhas taken a fork\033[0m"
# define ACTION_TEXT_EAT	"\033[0;32mis eating\033[0m"
# define ACTION_TEXT_SLEEP	"\033[0;30mis sleeping\033[0m"
# define ACTION_TEXT_THINK	"\033[0;34mthinking\033[0m"
# define ACTION_TEXT_DEAD	"\033[0;31mdied\033[0m"

# define ACTION_CODE_FORK	0
# define ACTION_CODE_EAT	1
# define ACTION_CODE_SLEEP	2
# define ACTION_CODE_THINK	3
# define ACTION_CODE_DEAD	4

# define MAX_ACTIONS		5

static char	*g_actions_string[MAX_ACTIONS] =
{
	ACTION_TEXT_FORK, ACTION_TEXT_EAT, ACTION_TEXT_SLEEP,
	ACTION_TEXT_THINK, ACTION_TEXT_DEAD
};

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
void	*ft_memcpy(void *dst, const void *src, size_t len);

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);

int		ft_strncmp(const char *s1, const char *s2, size_t len_mx);
int		parse_value(char const *arg, int *result);
int		ft_putnbr_str(int n, char *s);

# define NUMBER_OF_PHILOSOPHER						0
# define TIME_TO_DIE								1
# define TIME_TO_EAT								2
# define TIME_TO_SLEEP								3
# define NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT	4

void	*memset(void *s, int c, size_t n);

# define SPEAK_MUT 0
# define TABLE_MUT 1
# define DEATH_MUT 2

# define MUTEX_G_Q 3

typedef struct s_env {
	int					params[PARAM_Q];
	int					stop;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*mutex_bank;
	void				*p_envs;
	long				started_at;
}	t_env;

typedef struct s_philo_env {
	t_env		*env;
	int			f1;
	int			f2;
	int			num;
	int			state;
	pthread_t	th;
	int			eat_count;
	long		last_time[MAX_ACTIONS];
}	t_philo_env;

int		try_to_pick_up_fork(t_philo_env *p_env, int id);
long	get_base_timestamp(void);
long	get_current_timestamp(t_env *env);

void	clean_env(t_env *env);

int		do_action(t_philo_env *p_env, int action_code);
int		do_action_with_clean(t_philo_env *p_env, int action_code,
			int (*pre_action)(t_philo_env*),
			void (*clean_if_death_action)(t_philo_env*));
int		do_action_with_post(t_philo_env *p_env, int action_code,
			int (*post_action)(t_philo_env*));

int		get_last_ate(t_env *env, int i);
int		get_state(t_env *env, int i);
void	set_state(t_env *env, int i, int state);

int		my_usleep(t_env *env, int delay_in_millis, int max_time_before_death);
long	print_action(t_env *env, int id, int action_code);

int		quit(t_env *env, char *message, int exit_code);
void	*quit_philo(int exit_code, t_philo_env *p_env);

#endif
