/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/06 23:56:02 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watcher(long int *time_last_meal)
{
	t_table		*table;

	table = get_table();
	while (table->no_one_died == True)
	{
		sem_wait(table->sem_eat);
		*time_last_meal = get_time_now();
	}
	return (NULL);
}

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
	return (True);
}

static t_bool	open_semaphores(t_table *table)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_START_ALL);
	sem_unlink(SEM_START_EVEN);
	sem_unlink(SEM_EAT);
	table->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0744, table->nb_philo);
	if (table->sem_forks == SEM_FAILED)
		return (False);
	table->sem_write = sem_open(SEM_WRITE, O_CREAT, 0744, 1);
	if (table->sem_write == SEM_FAILED)
		return (False);
	table->sem_stop = sem_open(SEM_STOP, O_CREAT, 0744, 1);
	if (table->sem_stop == SEM_FAILED)
		return (False);
	table->sync_start.start_all = sem_open(SEM_START_ALL, O_CREAT, 0744, 0);
	if (table->sync_start.start_all == SEM_FAILED)
		return (False);
	table->sync_start.start_even = sem_open(SEM_START_EVEN, O_CREAT, 0744, 1);
	if (table->sync_start.start_even == SEM_FAILED)
		return (False);
	table->sem_eat = sem_open(SEM_EAT, O_CREAT, 0744, 1);
	if (table->sem_eat == SEM_FAILED)
		return (False);
	return (True);
}

static t_bool	handle_thread_creation_error(t_table *table, int i)
{
	print_error(THREAD_ERR_MSG);
	sem_wait(table->sem_forks);
	/* sem_wait(table->sync_start.start_all); */
	sem_wait(table->sync_start.start_even);
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
	/* sem_wait(table->sync_start.start_all); */
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
	/* sem_wait(table->sync_start.start_all); */
	/* sem_wait(table->sync_start.start_even); */
	if (launch_threads(table) == False)
		return (False);
	launch_process(table);
	return (monitor(table));
}
