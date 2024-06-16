/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:08:09 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/16 13:29:48 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void    kill_remaining_children(t_data_b *data)
{
    int i;
    
    i = 0;
    while (i < data->nb_of_philo)
    {
        if (data->pid[i] != -1)
            kill(data->pid[i], SIGTERM);
        i++;
    }
}

void parent_monitor(t_data_b *data)
{
    pid_t pid;
    int i;
    
    i = 0;
    pid = waitpid(-1, &data->status, 0);
    if (pid > 0)
    {
        while (i < data->nb_of_philo)
        {
            if (data->pid[i] == pid)
            {
                printf("Child process %d has terminated.\n", data->pid[i]);
                data->pid[i] = -1;
                break;
            }
            i++;
        }
    }
    kill_remaining_children(data);
}
