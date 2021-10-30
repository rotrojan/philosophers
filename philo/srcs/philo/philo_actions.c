/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:58:03 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/30 12:57:16 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_table *table, enum e_action action, int index)
{
	char const		*error_msg[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	pthread_mutex_lock(&table->write_mutex);
	printf("%6ld %d %s\n", get_time_now() - get_table()->time_start,
		index + 1, error_msg[action]);
	pthread_mutex_unlock(&table->write_mutex);
}

t_bool	philo_take_fork(t_table *table, int i, enum e_side side)
{
	t_bool	ret;

	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		pthread_mutex_lock(&table->fork[(i + side) % table->nb_philo].mutex);
	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		print_action(table, Take_fork, i);
	return (ret);
}

t_bool	philo_eat(t_table *table, int i)
{
	t_bool	ret;

	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		print_action(table, Eat, i);
	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		write_protected_data(&table->time_last_meal[i], get_time_now());
	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		msleep(table->time_to_eat);
	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		pthread_mutex_unlock(&table->fork[i].mutex);
	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		pthread_mutex_unlock(&table->fork[(i + 1) % table->nb_philo].mutex);
	return (ret);
}

t_bool	philo_sleep(t_table *table, int i)
{
	t_bool	ret;

	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		print_action(table, Sleep, i);
	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		msleep(table->time_to_sleep);
	return (False);
}

t_bool	philo_think(t_table *table, int i)
{
	t_bool	ret;

	ret = read_protected_data(&table->no_one_died);
	if (ret == True)
		print_action(table, Think, i);
	return (ret);
}
