/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:05:29 by lprates           #+#    #+#             */
/*   Updated: 2021/10/23 18:41:13 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H

# include "unistd.h"
# include "pthread.h"
# include "stdlib.h"
# include "stdio.h"
# include "time.h"
# include <sys/time.h>

typedef struct	s_philos
{
	pthread_t	philo;
	long long	last_meal;
}				t_philos;

// have to separate structs better, setting for example
typedef struct	s_data
{
	t_philos	*philos;
	pthread_mutex_t	*fork;
	pthread_mutex_t	increment;
	unsigned int	die_timer;
	unsigned int	eat_timer;
	unsigned int	slp_timer;
	unsigned int	eat_cnt;
	long long		time_in_usec;
	int	*cnt;
	int	dead;
	int	philo_nbr;
}				t_data;


int	ft_atoi(const char *str);

void	init_philos(t_data *forks, char *argv[]);

long long	get_curr_time(t_data *phil);

void	check_dead(t_data *phil);

#endif
