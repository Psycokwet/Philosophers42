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



#endif
