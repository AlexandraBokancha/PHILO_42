/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:18:13 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/28 17:55:23 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

long int	get_time_b(t_data_b *data)
{
	long int	ms;

	gettimeofday(data->tv, NULL);
	ms = (data->tv->tv_sec * 1000 + data->tv->tv_usec / 1000) - data->t_start;
	return (ms);
}

void	start_b(t_data_b *data)
{
	gettimeofday(data->tv, NULL);
	data->t_start = (data->tv->tv_sec * 1000) + (data->tv->tv_usec / 1000);
}

int	ft_atoi_b(const char *nptr)
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

int	is_digit_b(char **str)
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

int	ft_usleep_b(t_data_b *data, size_t time)
{
	size_t	start;

	start = get_time_b(data);
	while ((get_time_b(data) - start) < time)
		usleep(time * 100);
	return (0);
}
