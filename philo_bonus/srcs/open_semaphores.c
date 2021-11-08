/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:14:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/08 21:40:55 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	initialize_semaphore(char const *sem_name, sem_t **sem, int val)
{
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT, S_IRWXU | S_IROTH | S_IRGRP, val);
	if (*sem == SEM_FAILED)
		return (False);
	while (val > 0)
	{
		sem_post(*sem);
		--val;
	}
	return (True);
}

t_bool	open_semaphores(t_table *table)
{
	if (initialize_semaphore(SEM_FORKS, &table->sem_forks, table->nb_philo)
		== False)
		return (False);
	if (initialize_semaphore(SEM_WRITE, &table->sem_write, 1) == False)
		return (False);
	if (initialize_semaphore(SEM_STOP, &table->sem_stop, 1) == False)
		return (False);
	if (initialize_semaphore(SEM_SYNC_START, &table->sem_sync_start, 0)
		== False)
		return (False);
	if (initialize_semaphore(SEM_EAT, &table->sem_eat, 0) == False)
		return (False);
	if (initialize_semaphore(SEM_NO_ONE_DIED, &table->no_one_died.sem, 1)
		== False)
		return (False);
	if (initialize_semaphore(SEM_NB_PHILO_ATE_ENOUGH,
			&table->nb_philo_ate_enough.sem, 1) == False)
		return (False);
	if (initialize_semaphore(SEM_LAST_MEAL, &table->sem_last_meal, 1) == False)
		return (False);
	return (True);
}
