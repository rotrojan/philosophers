/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/08 22:39:24 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	allocate_data(t_table *table)
{
	table->philo = malloc(sizeof(*table->philo) * table->nb_philo);
	if (table->philo == NULL)
		return (False);
	table->time_last_meal = malloc(sizeof(*table->time_last_meal)
			* table->nb_philo);
	if (table->time_last_meal == NULL)
		return (False);
	table->fork = malloc(sizeof(*table->fork) * table->nb_philo);
	if (table->fork == NULL)
		return (False);
	return (True);
}

static t_bool	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork[i].mutex, NULL) != 0)
			return (False);
		table->fork[i].val = True;
		++i;
	}
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return (False);
	if (pthread_mutex_init(&table->no_one_died.mutex, NULL) != 0)
		return (False);
	return (True);
}

static t_bool	handle_thread_creation_error(t_table *table, int i)
{
	write_protected_data(&table->no_one_died, False);
	pthread_mutex_unlock(&table->sync_start.start_all);
	pthread_mutex_unlock(&table->sync_start.start_even);
	while (i > 0)
	{
		if (pthread_join(table->philo[i], NULL) != 0)
			print_error(JOIN_ERR_MSG);
		--i;
	}
	if (pthread_join(table->philo[i], NULL) != 0)
		print_error(JOIN_ERR_MSG);
	return (False);
}

static t_bool	launch_threads(t_table *table)
{
	int		i;
	int		*j;

	i = 0;
	while (i < table->nb_philo)
	{
		j = malloc(sizeof(*j));
		if (j == NULL)
		{
			print_error(MALLOC_ERR_MSG);
			return (handle_thread_creation_error(table, --i));
		}
		*j = i;
		if (pthread_create(&table->philo[i], NULL, &routine, j) != 0)
		{
			free(j);
			j = NULL;
			print_error(THREAD_ERR_MSG);
			return (handle_thread_creation_error(table, --i));
		}
		++i;
	}
	return (True);
}

t_bool	run_philo(t_table *table)
{
	int	i;

	if (allocate_data(table) == False)
		return (print_error(MALLOC_ERR_MSG));
	if (init_mutexes(table) == False)
		return (print_error(MUTEX_ERR_MSG));
	table->time_start = get_time_now();
	i = 0;
	while (i < table->nb_philo)
		table->time_last_meal[i++] = table->time_start;
	pthread_mutex_lock(&table->sync_start.start_all);
	pthread_mutex_lock(&table->sync_start.start_even);
	if (launch_threads(table) == False)
		return (False);
	return (monitor(table));
}
