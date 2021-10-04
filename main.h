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
# define PARAM_Q 5


# define ACTION_TEXT_FORK	"has taken a fork"
# define ACTION_TEXT_EAT	"is eating"
# define ACTION_TEXT_SLEEP	"is sleeping"
# define ACTION_TEXT_THINK	"is thinking"
# define ACTION_TEXT_DEAD	"died"

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

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);

int		ft_strncmp(const char *s1, const char *s2, size_t len_mx);
int		parse_value(char const *arg, int *result);

# define NUMBER_OF_PHILOSOPHER 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT 4

void *memset(void *s, int c, size_t n);

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


typedef struct s_env {
	int	params[PARAM_Q];
	pthread_mutex_t	*forks;
	pthread_mutex_t	speak;
	pthread_mutex_t	table;
} t_env;

typedef struct s_philo_env {
	t_env		*env;
	int			num;
	pthread_t	th;
	int			eat_count;
	long		last_ate;
} t_philo_env;

int		try_to_pick_up_fork(t_philo_env *p_env, int id);
long	get_current_timestamp();

long	print_action(t_env* env, int id, int action_code);

#endif
