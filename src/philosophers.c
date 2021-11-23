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

void	*start_sim(void *input)
{
	t_data		*data;
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
		if (can_take_forks(philo, philo->i, data))
		{
			philo_eating(philo, data);
			drops_forks(philo, philo->i, data);
			if (data->settings.meals_nbr && check_all_full(data))
				return (NULL);
			philo_sleeping_and_thinking(philo, data);
		}
	}
	return (NULL);
}

void	destroy_forks(t_data *data)
{
	while (data->settings.philo_nbr >= 0)
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
		if (pthread_create(&data->philos[cnt].thread, NULL, &start_sim, data))
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
