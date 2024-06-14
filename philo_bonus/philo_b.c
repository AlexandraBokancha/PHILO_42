/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:29:20 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/14 19:27:11 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

// initialiser et ouvrir un semaphore nomme (+etablie une connexion entre un sem et un processus)
// sem_t *sem_open(const char *name, int oflag);

// lock a sem
// int sem_wait(sem_t *sem); 
// prends le pointeur vers le sem a blocquer

// unlock a semaphore (like a signal() in a video)
// int sem_post(sem_t *sem);

int main(int ac, char **av)
{
	t_data_b	*data;
	t_sem_b		*sems;
	t_philo_b	*philo;
	pid_t		pid;
	int			status;
	
	if (ac < 5 || ac > 6)
		return (1);
	data = init_data_b(av, ac);
	if (!data)
		return (printf("Invalid argument.\n"), 1);
	sems = init_sem_b(data);
	philo = init_philo_b(data);
	pid = fork();
	if (pid == 0)
	{
		exit (0);
	}
	waitpid(-1, &status, 0);
	close_sems(data, sems);
	free(philo);
	free_data_b(data);
	return (0);
}