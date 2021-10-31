/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/31 02:56:57 by bigo             ###   ########.fr       */
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

static void	init_sides(int i, int nb_philo, t_side *first, t_side *second)
{
	first->is_taken = False;
	second->is_taken = False;
	if (i != nb_philo - 1)
	{
		first->side = Left;
		second->side = Right;
	}
	else
	{
		first->side = Right;
		second->side = Left;
	}
}

static void	routine_loop(t_table *table, int i, t_side *first, t_side *second)
{
	int	nb_time;

	nb_time = 0;
	while (check_end_simulation(table) == True)
	{
		if (philo_take_fork(table, i, first) == False)
			break ;
		if (philo_take_fork(table, i, second) == False)
			break ;
		if (philo_eat(table, i, first, second) == False)
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
	t_side		first;
	t_side		second;

	table = get_table();
	i = *(int *)index;
	free(index);
	sync_philo(table, i);
	init_sides(i, table->nb_philo, &first, &second);
	routine_loop(table, i, &first, &second);
	if (first.is_taken == True)
		pthread_mutex_unlock(&table->fork[(i + first.side) % table->nb_philo]);
	if (second.is_taken == True)
		pthread_mutex_unlock(&table->fork[(i + second.side) % table->nb_philo]);
	return (NULL);
}
