/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:58:03 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/08 19:19:57 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_table *table, enum e_action action, int index)
{
	char const		*error_msg[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
	};

	sem_wait(table->sem_write);
	printf("%6ld %d %s\n", get_time_now() - get_table()->time_start,
		index + 1, error_msg[action]);
	sem_post(table->sem_write);
}

void	philo_take_forks(t_table *table, int i)
{
	sem_wait(table->sem_stop);
	sem_wait(table->sem_forks);
	print_action(table, Take_fork, i);
	sem_wait(table->sem_forks);
	print_action(table, Take_fork, i);
	sem_post(table->sem_stop);
}

void	philo_eat(t_table *table, int i)
{
	sem_post(table->sem_eat);
	print_action(table, Eat, i);
	msleep(table->time_to_eat);
	sem_post(table->sem_forks);
	sem_post(table->sem_forks);
}

void	philo_sleep(t_table *table, int i)
{
	print_action(table, Sleep, i);
	msleep(table->time_to_sleep);
}

void	philo_think(t_table *table, int i)
{
	print_action(table, Think, i);
}
