/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:13:55 by albokanc          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:43 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_data(t_data *data, char **av, int ac)
{
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->nb_of_times_to_eat = ft_atoi(av[5]);
		if (data->nb_of_times_to_eat <= 0)
			return (free(data));
	}
	else
		data->nb_of_times_to_eat = -1;
}

int	death_status(t_philo *philo, int i, int run)
{
	set_dead(philo);
	print_dead(&philo[i]);
	run = 0;
	return (run);
}

void	full_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->m_print);
}
