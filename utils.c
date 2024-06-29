/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:38:35 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/29 22:07:52 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if ((nptr[i] == '-') || nptr[i] == '+')
	{	
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = 10 * n + (nptr[i] - '0');
		i++;
	}
	return (n * sign);
}

int	is_digit(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] >= '0' && str[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void	start(t_data *data)
{
	gettimeofday(data->tv, NULL);
	data->t_start = (data->tv->tv_sec * 1000) + (data->tv->tv_usec / 1000);
}

long int	get_time(t_data *data)
{
	long int	ms;

	//pthread_mutex_lock(&data->m_time);
	gettimeofday(data->tv, NULL);
	ms = (data->tv->tv_sec * 1000 + data->tv->tv_usec / 1000) - data->t_start;
	//pthread_mutex_unlock(&data->m_time);
	return (ms);
}

int	ft_usleep(t_data *data, useconds_t time)
{
	u_int64_t	start;

	start = get_time(data);
	while ((get_time(data) - start) < time)
		usleep(time / 10);
	return (0);
}
