/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:31:18 by lprates           #+#    #+#             */
/*   Updated: 2021/10/23 18:25:01 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eating(t_philos *philo, t_data *data)
{
	printf("%lu %d is eating\n", get_time(data), philo->i + 1);
	usleep(data->settings.eat_timer * 1000);
	return ;
}

void	philo_sleeping_and_thinking(t_philos *philo, t_data *data)
{
	if (!data->dead_philo)
		printf("%lu %d is sleeping\n", get_time(data), philo->i + 1);
	usleep(data->settings.slp_timer * 1000);
	if (!data->dead_philo)
		printf("%lu %d is thinking\n", get_time(data), philo->i + 1);
	return ;
}

int	check_all_full(t_data *data)
{
	int	i;
	int	full_count;

	i = -1;
	full_count = 0;
	while (++i < data->settings.philo_nbr)
		if (!data->philos[i].meals_left)
			full_count++;
	if (full_count == data->settings.philo_nbr)
		return (1);
	return (0);
}

void	drops_forks(t_philos *philo, int philo_i, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->i].fork);
	pthread_mutex_unlock(&data->forks[(philo->i + 1) % data->settings.philo_nbr].fork);
	data->forks[(philo_i + 1) % data->settings.philo_nbr].taken = 0;
	data->forks[philo_i].taken = 0;
	if (data->settings.meals_nbr && philo->meals_left)
		philo->meals_left--;
}

int	not_hungriest(int philo_i, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->settings.philo_nbr)
	{
		if (data->philos[i].last_meal < data->philos[philo_i].last_meal)
			return (1);
	}
	return (0);
}

int	can_take_forks(t_philos *philo, int philo_i, t_data *data)
{
	int		left;
	int		right;
	int		p_nbr;

	p_nbr = data->settings.philo_nbr;
	if (p_nbr > 1)
		left = data->forks[(philo_i + 1) % p_nbr].taken;
	right = data->forks[philo_i].taken;
	if (left || right || p_nbr <= 1 || not_hungriest(philo_i, data))
		return (0);
	data->forks[(philo_i + 1) % p_nbr].taken = 1;
	data->forks[philo_i].taken = 1;
	pthread_mutex_lock(&data->forks[(philo->i + 1) % p_nbr].fork);
	pthread_mutex_lock(&data->forks[philo->i].fork);
	philo->last_meal = get_time(data);
	printf("%lu %d has taken a fork\n", philo->last_meal, philo->i + 1);
	printf("%lu %d has taken a fork\n", philo->last_meal, philo->i + 1);
	return (1);
}

long	convert_usec_to_ms(long usec)
{
	return (usec / 1000);
}

long	timeval_to_usec(struct timeval *time)
{
	long	curr_time;

	curr_time = time->tv_sec * 1000000 + time->tv_usec;
	return (curr_time);
}

long	get_time_diff(struct timeval *present, struct timeval *past)
{
	long	time;

	time = (timeval_to_usec(present) - timeval_to_usec(past));
	return (convert_usec_to_ms(time));
}

/**
 * @brief Get the curr time object.
 * 
 * curr_time is the current time since
 * start of simulation
 * 
 * @param data  - main struct
 * @return long long with current time in ms
 */
long	get_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (get_time_diff(&time, &data->start_time));
}

int	check_dead(t_data *data)
{
	int		i;
	long	death_timer;
	long	curr_time;

	pthread_mutex_lock(&data->death_lock);
	i = 0;
	death_timer = 0;
	while (i < data->settings.philo_nbr)
	{
		curr_time = get_time(data);
		death_timer = curr_time - data->philos[i].last_meal;
		if (death_timer > data->settings.die_timer && !data->dead_philo)
		{
			//printf("i: %i, death timer: %lu, curr time: %lu, last meal: %lu\n", i, death_timer, curr_time, data->philos[i].last_meal);
			data->dead_philo = 1;
			printf("%lu %d died\n", \
					curr_time, data->philos[i].i + 1);
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
		else if (data->dead_philo)
		{
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}
