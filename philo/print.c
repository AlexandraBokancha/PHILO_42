/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:49:19 by albokanc          #+#    #+#             */
/*   Updated: 2024/07/19 15:35:01 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->stop || philo->dead)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("%ld %i has taken a fork\n", get_time(philo->data), philo->philo_nb);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->stop || philo->dead)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("\033[0;34m%ld %i is eating\033[0m\n", \
		get_time(philo->data), philo->philo_nb);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->stop || philo->dead)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("\033[0;32m%ld %i is sleeping\033[0m\n", \
		get_time(philo->data), philo->philo_nb);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->stop || philo->dead)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("\033[0;33m%ld %i is thinking\033[0m\n", \
		get_time(philo->data), philo->philo_nb);
	pthread_mutex_unlock(&philo->data->m_print);
	if (philo->philo_nb % 2 \
		&& philo->data->time_to_eat >= philo->data->time_to_sleep)
		usleep(((philo->data->time_to_eat - philo->data->time_to_sleep) \
			* 1000) + 1000);
}

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	printf("\033[0;31m%ld %i died\033[0m\n", \
		get_time(philo->data), philo->philo_nb);
	pthread_mutex_unlock(&philo->data->m_print);
}
