/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:08:09 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/30 21:16:25 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	kill_remaining_children(t_data_b *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (data->pid[i] != -1)
		{
			kill(data->pid[i], SIGKILL);
			//waitpid(-1, NULL, 0);
		}
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0);
}

void	*is_dead(void *data)
{
	t_data_b	*data_b;
	long int	t;

	data_b = (t_data_b *)data;
	while (1)
	{
		sem_wait(data_b->lock);
		t = get_time_b(data) - data_b->t_meal;
		sem_post(data_b->lock);
		if (t >= data_b->t_to_die)
			exit(3);
		else if (data_b->nb_of_meals != -1 && data_b->meal_count >= data_b->nb_of_meals)
			exit(2);
	}
	return (NULL);
}

void	parent_monitor(t_data_b *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		waitpid(-1, &data->status, 0);
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 3)
			{
				printf("\033[0;31m%ld %i died\033[0m\n", get_time_b(data),
				data->philo_id + 1);
				data->pid[i] = -1;
				break ;
			}
			else if (data->status == 2)
			{
				data->pid[i] = -1;
				break ;
			}
		}
		i++;
	}
	kill_remaining_children(data);
	close_sems(data);
}
