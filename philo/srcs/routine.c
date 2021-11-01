/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/01 23:36:00 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_end_simulation(t_table *table)
{
	return (read_protected_data(&table->no_one_died) == True
		&& read_protected_data(&table->nb_philo_ate_enough) != table->nb_philo);
}

static void	sync_philo(t_table *table, int i)
{
	pthread_mutex_lock(&table->sync_start.start_all);
	pthread_mutex_unlock(&table->sync_start.start_all);
	if (i % 2 == 1)
		increment_protected_data(&table->sync_start.odd_count);
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&table->sync_start.start_even);
		pthread_mutex_unlock(&table->sync_start.start_even);
	}
}

static void	routine_loop(t_table *table, int i)
{
	int	nb_time;

	nb_time = 0;
	while (check_end_simulation(table) == True)
	{
		if (philo_take_fork(table, i, Left) == False)
			break ;
		if (philo_take_fork(table, i, Right) == False)
			break ;
		if (philo_eat(table, i) == False)
			break ;
		if (table->nb_time_each_philo_must_eat != -1)
		{
			++nb_time;
			if (nb_time == table->nb_time_each_philo_must_eat)
			{
				increment_protected_data(&table->nb_philo_ate_enough);
				break ;
			}
		}
		if (philo_sleep(table, i) == False)
			break ;
		if (philo_think(table, i) == False)
			break ;
	}
}

void	*routine(void *index)
{
	t_table		*table;
	int			i;

	table = get_table();
	i = *(int *)index;
	free(index);
	sync_philo(table, i);
	routine_loop(table, i);
	return (NULL);
}
