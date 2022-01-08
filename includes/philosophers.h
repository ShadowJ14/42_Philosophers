/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:05:29 by lprates           #+#    #+#             */
/*   Updated: 2022/01/08 00:47:50 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "unistd.h"
# include "pthread.h"
# include "stdlib.h"
# include "stdio.h"
# include "time.h"
# include <sys/time.h>

typedef struct s_philos
{
	int				i;
	pthread_t		thread;
	long			last_meal;
	int				had_meal;
	int				meals_left;
}				t_philos;

typedef struct s_forks
{
	pthread_mutex_t	fork;
	int				taken;
}				t_forks;

typedef struct s_settings
{
	int				philo_nbr;
	unsigned int	meals_nbr;
	unsigned int	die_timer;
	unsigned int	eat_timer;
	unsigned int	slp_timer;
}				t_settings;

// have to separate structs better, setting for example
typedef struct s_data
{
	t_philos		*philos;
	t_settings		settings;
	t_forks			*forks;
	pthread_mutex_t	increment;
	pthread_mutex_t	meals_left_lock;
	pthread_mutex_t	death_lock;
	long			time_in_usec;
	int				dead_philo;
	struct timeval	start_time;
}				t_data;

int		ft_atoi(const char *str);
int		init_philos(t_data *data, char *argv[]);
long	get_time(t_data *data);
int		check_dead(t_data *data);
long	timeval_to_usec(struct timeval *time);
long	convert_usec_to_ms(long usec);
int		can_take_forks(t_philos *philo, int philo_i, t_data *data);
void	drops_forks(t_philos *philo, int philo_i, t_data *data);
int		check_all_full(t_data *data);
void	philo_eating(t_philos *philo, t_data *data);
int		philo_sleeping_and_thinking(t_philos *philo, t_data *data);
int		error_handling(int error, t_data *data);
void	destroy_forks(t_data *data);

#endif
