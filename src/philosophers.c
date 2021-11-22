/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:05:05 by lprates           #+#    #+#             */
/*   Updated: 2021/10/23 18:41:59 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*test(void *input)
{
	t_data		*data;
	long		curr_time;
	t_philos	*philo;
	static int	index = 0;

	data = input;
	pthread_mutex_lock(&data->increment);
	philo = &data->philos[index++];
	pthread_mutex_unlock(&data->increment);
	while (!data->dead_philo)
	{
		if (check_dead(data))
			return (NULL);
		if (can_take_forks(philo->index, data))
		{
			curr_time = get_curr_time(data);
			philo->last_meal = curr_time;
			if (!data->dead_philo)
			{
				printf("%lums Philosopher: %d has taken a fork\n", curr_time, philo->index + 1);
				printf("%lums Philosopher: %d has taken a fork\n", curr_time, philo->index + 1);
			}
			pthread_mutex_lock(&data->forks[(philo->index + 1) % data->settings.philo_nbr].fork);
			pthread_mutex_lock(&data->forks[philo->index].fork);
			if (!data->dead_philo)
				printf("%lums Philosopher: %d is eating\n", get_curr_time(data), philo->index + 1);
			usleep(data->settings.eat_timer * 1000);
			pthread_mutex_unlock(&data->forks[philo->index].fork);
			pthread_mutex_unlock(&data->forks[(philo->index + 1) % data->settings.philo_nbr].fork);
			drops_forks(philo->index, data);
			if (data->settings.meals_nbr)
			{
				if (philo->meals_left)
					philo->meals_left--;
				if (check_all_full(data))
					return (NULL);
			}
			curr_time = get_curr_time(data);
			if (!data->dead_philo)
				printf("%lums Philosopher: %d is sleeping\n", curr_time, philo->index + 1);
			usleep(data->settings.slp_timer * 1000);
			if (!data->dead_philo)
				printf("%lums Philosopher: %d is thinking\n", get_curr_time(data), philo->index + 1);
		}
	}
	return (NULL);
}

void	destroy_forks(t_data *data)
{
	while (data->settings.philo_nbr <= 0)
		pthread_mutex_destroy(&data->forks[data->settings.philo_nbr--].fork);
	pthread_mutex_destroy(&data->increment);
	free(data->forks);
	free(data->philos);
	free(data);
}

int	create_philos(t_data *data)
{
	int	cnt;

	cnt = -1;
	while (++cnt < data->settings.philo_nbr)
		pthread_mutex_init(&data->forks[cnt].fork, NULL);
	pthread_mutex_init(&data->increment, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	cnt = -1;
	while (++cnt < data->settings.philo_nbr)
	{
		if (pthread_create(&data->philos[cnt].thread, NULL, &test, data))
			return (-1);
	}
	cnt = -1;
	while (++cnt < data->settings.philo_nbr)
		if (pthread_join(data->philos[cnt].thread, NULL))
			return (-1);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data			*data;

	if (argc < 5 || argc > 6)
		return (-1);
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (-1);
	if (gettimeofday(&data->start_time, NULL))
		return (-1);
	init_philos(data, argv);
	if (!data->philos || !data->forks)
		return (-1);
	create_philos(data);
	destroy_forks(data);
}
