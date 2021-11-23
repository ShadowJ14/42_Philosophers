/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:31:18 by lprates           #+#    #+#             */
/*   Updated: 2021/11/23 22:04:59 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	convert_usec_to_ms(long usec)
{
	return (usec / 1000);
}

long	timeval_to_usec(struct timeval *time)
{
	long	curr_time;

	curr_time = time->tv_sec * 1000000 + time->tv_usec;
	return (curr_time);
}

long	get_time_diff(struct timeval *present, struct timeval *past)
{
	long	time;

	time = (timeval_to_usec(present) - timeval_to_usec(past));
	return (convert_usec_to_ms(time));
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
long	get_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (get_time_diff(&time, &data->start_time));
}

int	ft_atoi(const char *str)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		ret *= 10;
		ret += (sign * (*(str++) - '0'));
		if (ret > 2147483647)
			return (-1);
		if (ret < -2147483648)
			return (0);
	}
	return (ret);
}
