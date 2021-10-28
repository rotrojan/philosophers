/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/28 21:10:54 by rotrojan         ###   ########.fr       */
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
		++i;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->time_last_meal[i].mutex, NULL) != 0)
			return (False);
		++i;
	}
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return (False);
	if (pthread_mutex_init(&table->is_finished.mutex, NULL) != 0)
		return (False);
	return (True);
}

static t_bool	launch_threads(t_table *table)
{
	int		i;
	int		*j;
	t_bool	ret;

	i = 0;
	ret = True;
	while (i < table->nb_philo)
	{
		j = malloc(sizeof(*j));
		if (j == NULL)
		{
			ret = False;
			print_error(MALLOC_ERR_MSG);
		}
		*j = i;
		if (pthread_create(&table->philo[i], NULL, &routine, j) != 0)
		{
			ret = False;
			print_error(THREAD_ERR_MSG);
			break ;
		}
		++i;
	}
	return (ret);
}

t_bool	join_threads(t_table *table)
{
	int		i;
	t_bool	ret;

	i = 0;
	ret = True;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->philo[i], NULL) != 0)
			ret = False;
		++i;
	}
	return (ret);
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
		write_protected_data(&table->time_last_meal[i++], table->time_start);
	if (launch_threads(table) == False)
	{
		join_threads(table);
		return (False);
	}
	return (monitor(table));
}
