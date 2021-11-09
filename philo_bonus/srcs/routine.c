/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/09 00:46:53 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	check_end_simulation(t_table *table)
{
	return (read_protected_data(&table->no_one_died) == True
		&& read_protected_data(&table->nb_philo_ate_enough) != table->nb_philo);
}

void	routine(int i)
{
	t_table		*table;

	table = get_table();
	sem_wait(table->sem_sync_start);
	sem_post(table->sem_sync_start);
	while (check_end_simulation(table) == True)
	{
		philo_take_forks(table, i);
		philo_eat(table, i);
		philo_sleep(table, i);
		philo_think(table, i);
	}
}
