/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:49:19 by albokanc          #+#    #+#             */
/*   Updated: 2024/05/09 15:00:03 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->stop > 0 || philo->dead > 0)
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
	if (philo->data->stop > 0 || philo->dead > 0)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("%ld %i is eating\n", get_time(philo->data), philo->philo_nb);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->stop > 0 || philo->dead > 0)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("%ld %i is sleeping\n", get_time(philo->data), philo->philo_nb);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	print_think(t_philo *philo)
{
	int	t_eat;
	int	t_sleep;

	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->stop > 0 || philo->dead > 0)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	printf("%ld %i is thinking\n", get_time(philo->data), philo->philo_nb);
	pthread_mutex_unlock(&philo->data->m_print);
	if ((philo->philo_nb % 2)
		&& (philo->data->time_to_eat >= philo->data->time_to_sleep))
		usleep(((t_eat - t_sleep) * 1000) + 1000);
}

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	printf("%ld %i died\n", get_time(philo->data), philo->philo_nb);
	pthread_mutex_unlock(&philo->data->m_print);
}
