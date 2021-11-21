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
	//t_data	phil;
	t_data	*data;
	long long curr_time;
	static int	index = -1;
	
	data = input;
	pthread_mutex_lock(&data->increment);
	index++;
	pthread_mutex_unlock(&data->increment);
	//curr_time = get_curr_time(phil);
	while(1)
	{
		pthread_mutex_lock(&data->forks[(index + 1) % 4]);
		printf("%llums Philosopher: %d has taken a fork\n", get_curr_time(data), index + 1);
		// must change this to nb of philos var
		if (data->philos[index].last_meal.tv_sec)
			check_dead(data);
		pthread_mutex_lock(&data->forks[index]);
		printf("%llums Philosopher: %d has taken a fork\n", get_curr_time(data), index + 1);
		printf("%llums Philosopher: %d is eating\n", get_curr_time(data), index + 1);
		// eating timer
		usleep(data->settings->eat_timer * 1000);
		if (data->philos[index].last_meal.tv_sec)
			check_dead(data);
		
		pthread_mutex_unlock(&data->forks[index]);
		// must change this to nb of philos var
		pthread_mutex_unlock(&data->forks[(index + 1) % 4]);
		curr_time = get_curr_time(data);
		data->philos[index].last_meal = curr_time;
		printf("%llums Philosopher: %d is sleeping\n", curr_time, index + 1);
		//printf("sleeptimer: %i\n", data->slp_timer);
		usleep(data->settings->slp_timer * 1000);
		printf("%llums Philosopher: %d is thinking\n", get_curr_time(data), index + 1);

	}

	return (NULL);
}

void	destroy_forks(t_data *data)
{
	// int	count;

	// count = -1;
	while (data->settings->philo_nbr <= 0)
		pthread_mutex_destroy(&data->forks[data->settings->philo_nbr--]);
	pthread_mutex_destroy(&data->increment);
	// while (++count < forks->philo_nbr)
	// 	free(forks->cnt[count]);
	//free(forks->cnt);
	free(data);
}

int	create_philos(t_data *forks)
{
	int	cnt;

	cnt = -1;
	while (++cnt < forks->settings->philo_nbr)
		pthread_mutex_init(&forks->forks[cnt], NULL);
	pthread_mutex_init(&forks->increment, NULL);
	cnt = -1;
	while (++cnt < forks->settings->philo_nbr)
	{
		// forks->cnt = malloc(sizeof(int));
		// \*forks->cnt = cnt;
		if (pthread_create(&forks->philos[cnt].thread, NULL, &test, forks))
			return (-1);
		//usleep(10);
	}
	cnt = -1;
	while (++cnt < forks->settings->philo_nbr)
		if (pthread_join(forks->philos[cnt].thread, NULL))
			return (-1);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data			*data;
	struct timeval	*start_time;
	//int c;	

	if (argc < 5 || argc > 6)
		return (-1);
	if (gettimeofday(&start_time, NULL))
		return (-1);
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (-1);
	data->time_in_usec = timeval_to_usec(start_time);
	init_philos(data, argv);
	if (!data->philos || !data->forks)
		return (-1);
	create_philos(data);
	destroy_forks(data);
}
