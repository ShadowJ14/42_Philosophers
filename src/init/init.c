/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:54:01 by lprates           #+#    #+#             */
/*   Updated: 2021/10/23 18:41:07 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos(t_data *data, char *argv[])
{
	int	i;

	i = -1;
	data->settings.philo_nbr = ft_atoi(argv[1]);
	data->settings.die_timer = ft_atoi(argv[2]);
	data->settings.eat_timer = ft_atoi(argv[3]);
	data->settings.slp_timer = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->settings.meals_nbr = ft_atoi(argv[5]);
		//printf("%d %d %d %d %d\n", philo_nbr, data->die_timer, data->eat_timer, data->slp_timer, data->eat_cnt);
	}
		//printf("%d %d %d %d\n", philo_nbr, data->die_timer, data->eat_timer, data->slp_timer);
	data->philos = malloc(sizeof(t_philos) * (data->settings.philo_nbr));
	data->forks = malloc(sizeof(t_forks) * data->settings.philo_nbr);
	while (++i < data->settings.philo_nbr)
	{
		data->philos[i].last_meal = 0;
		data->philos[i].index = i;
		data->forks[i].taken = 0;
		if (argv[5])
			data->philos[i].meals_left = data->settings.meals_nbr;
		
	}
	data->dead_philo = 0;
}
