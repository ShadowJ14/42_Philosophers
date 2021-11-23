/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 22:24:08 by lprates           #+#    #+#             */
/*   Updated: 2021/11/23 23:05:59 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_handling(int error, t_data *data)
{
	if (error == -1)
	{
		printf("Wrong number of arguments.\n");
		printf("Usage: ./philo nb_of_philos time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
	if (error == -2)
		printf("Failed at allocating necessary memory.\n");
	if (error == -3)
	{
		free(data);
		printf("Failed to get time of day.\n");
	}
	if (error == -4)
	{
		printf("Error while initializing philos.\n");
		destroy_forks(data);
	}
	if (error == -5)
	{
		printf("Error while creating or joining threads.\n");
		destroy_forks(data);
	}
	return (error);
}
