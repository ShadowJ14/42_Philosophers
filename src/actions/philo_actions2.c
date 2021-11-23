/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:44:18 by lprates           #+#    #+#             */
/*   Updated: 2021/11/23 22:02:47 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_data *data)
{
	int		i;
	long	death_timer;
	long	curr_time;

	pthread_mutex_lock(&data->death_lock);
	i = -1;
	death_timer = 0;
	while (++i < data->settings.philo_nbr)
	{
		curr_time = get_time(data);
		death_timer = curr_time - data->philos[i].last_meal;
		if (death_timer > data->settings.die_timer && !data->dead_philo)
		{
			data->dead_philo = 1;
			printf("%lu %d died\n", \
					curr_time, data->philos[i].i + 1);
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
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
