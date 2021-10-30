/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/30 23:15:25 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sync_philo(t_table *table, int i)
{
	pthread_mutex_lock(&table->sync_start.start_all);
	pthread_mutex_unlock(&table->sync_start.start_all);
	if (i % 2 == 1)
	{
		write_protected_data(&table->sync_start.odd_count,
			read_protected_data(&table->sync_start.odd_count) + 1);
	}
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
	while (read_protected_data(&table->no_one_died) == True)
	{
		if (philo_take_fork(table, i, first) == False)
			break ;
		if (philo_take_fork(table, i, second) == False)
			break ;
		if (philo_eat(table, i, first, second) == False)
			break ;
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
