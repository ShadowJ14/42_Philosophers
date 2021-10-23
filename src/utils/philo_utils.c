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

long long	get_curr_time(t_data *forks)
{
	struct timeval	time;
	long long	curr_time;
	long long	diff;

	if (gettimeofday(&time, NULL))
		return (-1);
	curr_time = time.tv_sec * 1000000 + time.tv_usec;
	diff = (curr_time - forks->time_in_usec) / 1000;
	return (diff);
}

void	check_dead(t_data *phil)
{
	int	i;
	long	death_timer;
	long long	curr_time;

	i = 0;
	death_timer = 0;
	while (i < 4)
	{
		curr_time = get_curr_time(phil);
		death_timer = curr_time - phil->philos[i].last_meal;
		if (death_timer > phil->die_timer)
		{
			phil->dead = 1;
			printf("%llums Philosopher: %d died\n", curr_time, *phil->cnt);
			exit(-1);
		}
		i++;
	}
}
