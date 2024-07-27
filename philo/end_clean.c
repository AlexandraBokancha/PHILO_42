/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:33:06 by albokanc          #+#    #+#             */
/*   Updated: 2024/05/09 14:09:25 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	joining(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_of_philo)
	{	
		if (pthread_join(philo[i].tid, NULL))
		{
			printf("Error while joining.\n");
			clean_all(philo, philo->data);
			exit(1);
		}
		i++;
	}
}

void	clean_all(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_of_philo)
	{
		pthread_mutex_destroy(&philo[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_meal);
	pthread_mutex_destroy(&data->m_control);
	pthread_mutex_destroy(&data->m_time);
	pthread_mutex_destroy(&data->m_stop);
	free(data->tv);
	free(data);
	free(philo);
}
