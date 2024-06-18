/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_clean_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:22:46 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/18 18:59:37 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	close_sems(t_data_b *data)
{
	sem_close(data->forks);
	sem_unlink("/fork");
	sem_close(data->lock);
	sem_unlink("/lock");
}

void	free_data_b(t_data_b *data)
{
	free(data->tv);
	free(data);
}

