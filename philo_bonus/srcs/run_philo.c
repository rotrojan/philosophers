/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/05 01:07:55 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	open_semaphores(t_table *table)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_STOP);
	table->forks = sem_open(SEM_FORKS, O_CREAT, 0744, table->nb_philo);
	if (table->forks == SEM_FAILED)
		return (False);
	table->sem_write = sem_open(SEM_WRITE, O_CREAT, 0744, 1);
	if (table->forks == SEM_FAILED)
		return (False);
	table->sem_stop = sem_open(SEM_STOP, O_CREAT, 0744, 1);
	if (table->sem_write == SEM_FAILED)
		return (False);
	return (True);
}

static t_bool	launch_forks(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->pid[i] = fork();
		if (table->pid[i] == -1)
			return (print_error(FORK_ERR_MSG));
		if (table->pid[i] == 0)
		{
			routine(i, table);
			break ;
		}
		++i;
	}
	return (True);
}

t_bool	run_philo(t_table *table)
{
	int		i;

	table->time_start = get_time_now();
	if (open_semaphores(table) == False)
		return (print_error(SEM_OPEN_ERR_MSG));
	table->pid = malloc(sizeof(*table->pid) * table->nb_philo);
	if (table->pid == NULL)
		return (print_error(MALLOC_ERR_MSG));
	if (launch_forks(table) == False)
		return (False);
	i = 0;
	while (i < table->nb_philo)
	{
		waitpid(table->pid[i], NULL, 0);
		++i;
	}
	return (True);
}
