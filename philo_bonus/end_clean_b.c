/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_clean_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:22:46 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/16 10:09:04 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	close_sems(t_data_b *data)
{
	(void)data;
	sem_unlink("/fork");
	sem_unlink("/lock");
	//free(data->sems);
}

void	free_data_b(t_data_b *data)
{
	free(data->tv);
	free(data);
}

