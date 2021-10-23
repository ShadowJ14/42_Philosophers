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

void	*test(void *forks)
{
	//t_data	phil;
	t_data	*cast;
	long long curr_time;
	static int	index = -1;
	
	cast = forks;
	pthread_mutex_lock(&cast->increment);
	index++;
	pthread_mutex_unlock(&cast->increment);
	//curr_time = get_curr_time(phil);
	while(1)
	{
		pthread_mutex_lock(&cast->fork[index]);
		printf("%llums Philosopher: %d has taken a fork\n", get_curr_time(cast), index + 1);
		// must change this to nb of philos var
		pthread_mutex_lock(&cast->fork[(index + 1) % 4]);
		printf("%llums Philosopher: %d has taken a fork\n", get_curr_time(cast), index + 1);
		printf("%llums Philosopher: %d is eating\n", get_curr_time(cast), index + 1);
		if (cast->philos[index].last_meal)
			check_dead(cast);
		usleep(cast->eat_timer * 1000);
		if (cast->philos[index].last_meal)
			check_dead(cast);
		
		pthread_mutex_unlock(&cast->fork[index]);
		// must change this to nb of philos var
		pthread_mutex_unlock(&cast->fork[(index + 1) % 4]);
		curr_time = get_curr_time(cast);
		cast->philos[index].last_meal = curr_time;
		printf("%llums Philosopher: %d is sleeping\n", curr_time, index + 1);
		//printf("sleeptimer: %i\n", cast->slp_timer);
		usleep(cast->slp_timer * 1000);
		printf("%llums Philosopher: %d is thinking\n", get_curr_time(cast), index + 1);

	}

	return (NULL);
}

void	destroy_forks(t_data *forks)
{
	while (forks->philo_nbr <= 0)
		pthread_mutex_destroy(&forks->fork[forks->philo_nbr--]);
	pthread_mutex_destroy(&forks->increment);
}

int	create_philos(t_data *forks)
{
	int	cnt;

	cnt = -1;
	while (++cnt < forks->philo_nbr)
		pthread_mutex_init(&forks->fork[cnt], NULL);
	pthread_mutex_init(&forks->increment, NULL);
	cnt = -1;
	while (++cnt < forks->philo_nbr)
	{
		forks->cnt = malloc(sizeof(int));
		*forks->cnt = cnt;
		if (pthread_create(&forks->philos[cnt].philo, NULL, &test, forks))
			return (-1);
		//usleep(10);
	}
	cnt = -1;
	while (++cnt < forks->philo_nbr)
		if (pthread_join(forks->philos[cnt].philo, NULL))
			return (-1);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	*forks;
	struct timeval	start_time;
	int c;	

	if (argc < 5 || argc > 6)
		return (-1);
	if (gettimeofday(&start_time, NULL))
		return (-1);
	forks = malloc(sizeof(t_data) * 1);
	if (!forks)
		return (-1);
	forks->time_in_usec = start_time.tv_sec * 1000000 + start_time.tv_usec;
	init_philos(forks, argv);
	if (!forks->philos || !forks->fork)
		return (-1);
	c = create_philos(forks);
	destroy_forks(forks);
}
