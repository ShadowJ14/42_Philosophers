/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:40:12 by lprates           #+#    #+#             */
/*   Updated: 2022/01/08 00:19:04 by lprates          ###   ########.fr       */
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

	left = 0;
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

void	drops_forks(t_philos *philo, int philo_i, t_data *data)
{
	int	p_nbr;

	p_nbr = data->settings.philo_nbr;
	pthread_mutex_unlock(&data->forks[(philo->i + 1) % p_nbr].fork);
	pthread_mutex_unlock(&data->forks[philo->i].fork);
	data->forks[(philo_i + 1) % p_nbr].taken = 0;
	data->forks[philo_i].taken = 0;
	if (data->settings.meals_nbr && philo->meals_left)
		philo->meals_left--;
}
