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
	int				index;
	pthread_t		thread;
	long	last_meal;
	int				had_meal;
	int				meals_left;
}				t_philos;

typedef struct	s_settings
{
	int				philo_nbr;
	unsigned int	meals_nbr;
	unsigned int	die_timer;
	unsigned int	eat_timer;
	unsigned int	slp_timer;
}				t_settings;


// have to separate structs better, setting for example
typedef struct	s_data
{
	t_philos		*philos;
	t_settings		*settings;
	pthread_mutex_t	*forks;
	pthread_mutex_t	increment;
	pthread_mutex_t meals_left_lock;
	pthread_mutex_t death_lock;
	long long		time_in_usec;
	int				dead_philo;
	struct timeval	start_time;

}				t_data;


int		ft_atoi(const char *str);
void	init_philos(t_data *data, char *argv[]);
long	get_curr_time(t_data *data);
void	check_dead(t_data *data);
long	timeval_to_usec(struct timeval *time);

#endif
