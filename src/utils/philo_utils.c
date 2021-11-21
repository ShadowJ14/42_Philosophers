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

long convert_usec_to_ms(long usec)
{
	return (usec / 1000);
}

long timeval_to_usec(struct timeval *time)
{
	long	curr_time;

	curr_time = time->tv_sec * 1000000 + time->tv_usec;
	return (curr_time);
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
long get_curr_time(t_data *data)
{
	struct timeval	*time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (get_time_diff(time, data->time_in_usec));
}

void	check_dead(t_data *data)
{
	int	i;
	long	death_timer;
	long long	curr_time;

	i = 0;
	death_timer = 0;
	while (i < 4)
	{
		curr_time = get_curr_time(data);
		death_timer = curr_time - data->philos[i].last_meal;
		if (death_timer > data->settings->die_timer)
		{
			data->dead_philo = 1;
			printf("%llums Philosopher: %d died\n", curr_time, data->settings->philo_nbr);
			exit(-1);
		}
		i++;
	}
}

long get_time_diff(struct timeval *present, struct timeval *past)
{
	long time;

	time = (timeval_to_usec(present) - timeval_to_usec(past));
	return(convert_usec_to_ms(time));
}
