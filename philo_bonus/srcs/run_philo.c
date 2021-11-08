/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/08 20:15:11 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	allocate_data(t_table *table)
{
	table->watcher = malloc(sizeof(*table->watcher) * table->nb_philo);
	if (table->watcher == NULL)
		return (False);
	table->time_last_meal = malloc(sizeof(*table->time_last_meal)
			* table->nb_philo);
	if (table->time_last_meal == NULL)
		return (False);
	table->pid = malloc(sizeof(*table->pid) * table->nb_philo);
	if (table->pid == NULL)
		return (False);
	memset(table->pid, 0, sizeof(table->nb_philo));
	return (True);
}

static t_bool	handle_thread_creation_error(t_table *table, int i)
{
	print_error(THREAD_ERR_MSG);
	sem_wait(table->sem_forks);
	sem_wait(table->sem_sync_start);
	while (i > 0)
	{
		if (pthread_join(table->watcher[i], NULL) != 0)
			print_error(JOIN_ERR_MSG);
		--i;
	}
	if (pthread_join(table->watcher[i], NULL) != 0)
		print_error(JOIN_ERR_MSG);
	return (False);
}

static t_bool	launch_threads(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->watcher[i], NULL,
				(void *(*)(void *))watcher, &table->time_last_meal[i]) != 0)
			return (handle_thread_creation_error(table, --i));
		++i;
	}
	return (True);
}

static t_bool	launch_process(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->pid[i] = fork();
		if (table->pid[i] == -1)
			return (print_error(FORK_ERR_MSG));
		if (table->pid[i] == 0)
		{
			routine(i);
			exit(EXIT_SUCCESS);
		}
		else
			++i;
	}
	return (True);
}

t_bool	run_philo(t_table *table)
{
	int	i;

	if (allocate_data(table) == False)
		return (print_error(MALLOC_ERR_MSG));
	if (open_semaphores(table) == False)
		return (print_error(SEM_OPEN_ERR_MSG));
	table->time_start = get_time_now();
	i = 0;
	while (i < table->nb_philo)
		table->time_last_meal[i++] = table->time_start;
	if (launch_threads(table) == False)
		return (False);
	if (launch_process(table) == False)
	{
		write_protected_data(&table->no_one_died, False);
		join_threads(table);
		kill(0, SIGINT);
		return (False);
	}
	monitor(table);
	return (True);
}
