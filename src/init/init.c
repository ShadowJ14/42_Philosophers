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

void	init_philos(t_data *forks, char *argv[])
{
	int	i;

	i = -1;
	forks->philo_nbr = ft_atoi(argv[1]);
	forks->die_timer = ft_atoi(argv[2]);
	forks->eat_timer = ft_atoi(argv[3]);
	forks->slp_timer = ft_atoi(argv[4]);
	if (argv[5])
	{
		forks->eat_cnt = ft_atoi(argv[5]);
		//printf("%d %d %d %d %d\n", philo_nbr, forks->die_timer, forks->eat_timer, forks->slp_timer, forks->eat_cnt);
	}
	else;
		//printf("%d %d %d %d\n", philo_nbr, forks->die_timer, forks->eat_timer, forks->slp_timer);
	forks->philos = malloc(sizeof(t_philos) * (forks->philo_nbr));
	forks->fork = malloc(sizeof(pthread_mutex_t) * forks->philo_nbr);
	while (++i < forks->philo_nbr)
		forks->philos[i].last_meal = 0;
	forks->dead = 0;
}
