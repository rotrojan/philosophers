/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/26 20:13:29 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	return_error()
{
	return (False);
}

void	print_action(enum e_action action, int index)
{
	struct timeval	tv;
	char const		*error_msg[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	gettimeofday(&tv, NULL);
	printf("%ld %d %s\n",
		tv.tv_sec * 1000 + tv.tv_usec / 1000 - get_table()->time_start,
		index + 1, error_msg[action]);
}

void	*routine(void *index)
{
	t_table			*table;
	int				i;
	struct timeval	tv;

	table = get_table();
	i = *(int *)index;
	free(index);
	while (True)
	{
		if (table->is_finished == False)
		{
			pthread_mutex_lock(&table->fork[i]);
			print_action(Take_fork, i);
		}
		else
			break ;
		if (table->is_finished == False)
		{
			pthread_mutex_lock(&table->fork[(i + 1) % table->nb_philo]);
			print_action(Take_fork, i);
		}
		else
			break ;
		if (table->is_finished == False)
		{
			print_action(Eat, i);
			gettimeofday(&tv, NULL);
			table->time_last_meal[i] = tv.tv_sec * 1000 + tv.tv_usec / 1000;
			usleep(table->time_to_eat * 1000);
			pthread_mutex_unlock(&table->fork[i]);
			pthread_mutex_unlock(&table->fork[(i + 1) % table->nb_philo]);
		}
		else
			break ;
		if (table->is_finished == False)
		{
			print_action(Sleep, i);
			usleep(table->time_to_sleep * 1000);
		}
		else
			break ;
		if (table->is_finished == False)
			print_action(Think, i);
		else
			break ;
	}
	return (NULL);
}

t_bool	allocate_data(t_table *table)
{
	table->philo = malloc(sizeof(*table->philo) * table->nb_philo);
	if (table->philo == NULL)
		return (False);
	table->time_last_meal = malloc(sizeof(*table->philo) * table->nb_philo);
	if (table->time_last_meal == NULL)
		return (False);
	table->fork = malloc(sizeof(*table->fork) * table->nb_philo);
	if (table->fork == NULL)
		return (False);
	return (True);
}

t_bool	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
			return (return_error());
		++i;
	}
	return (True);
}

t_bool	run_philo(t_table *table)
{
	struct timeval	tv;
	int				i;
	int				*j;

	if (allocate_data(table) == False)
		return (return_error());
	if (init_mutexes(table) == False)
		return (return_error());
	gettimeofday(&tv, NULL);
	table->time_start = tv.tv_sec * 1000 + tv.tv_sec / 1000;
	i = 0;
	while (i < table->nb_philo)
	{
		j = malloc(sizeof(*j));
		if (j == NULL)
			return (return_error());
		*j = i;
		if (pthread_create(&table->philo[i], NULL, &routine, j) != 0)
			return (return_error());
		++i;
	}
	i = 0;
	while (True)
	{
		while (i < table->nb_philo)
		{
			gettimeofday(&tv, NULL);
			if (tv.tv_sec * 1000 + tv.tv_usec / 1000 - table->time_last_meal[i]
					< table->time_to_die)
			{
				table->is_finished = True;
				print_action(Die, i);
			}
			++i;
		}
	}
	return (True);
}
