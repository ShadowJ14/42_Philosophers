/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:05:05 by lprates           #+#    #+#             */
/*   Updated: 2022/01/08 00:48:07 by lprates          ###   ########.fr       */
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
			if (philo_sleeping_and_thinking(philo, data))
				return (NULL);
		}
	}
	return (NULL);
}

void	destroy_forks(t_data *data)
{
	while (data->settings.philo_nbr >= 0)
		pthread_mutex_destroy(&data->forks[data->settings.philo_nbr--].fork);
	pthread_mutex_destroy(&data->increment);
	pthread_mutex_destroy(&data->death_lock);
	if (data->forks)
		free(data->forks);
	if (data->philos)
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
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data			*data;

	data = NULL;
	if (argc < 5 || argc > 6)
		return (error_handling(-1, data));
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (error_handling(-2, data));
	if (gettimeofday(&data->start_time, NULL))
		return (error_handling(-3, data));
	if (init_philos(data, argv))
		return (error_handling(-4, data));
	if (create_philos(data))
		return (error_handling(-5, data));
	destroy_forks(data);
}
