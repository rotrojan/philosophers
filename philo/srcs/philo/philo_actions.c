/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bigo </var/spool/mail/bigo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:47:12 by bigo              #+#    #+#             */
/*   Updated: 2021/10/28 01:23:45 by bigo             ###   ########.fr       */
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
	pthread_mutex_lock(&table->is_finished_mutex);
	if (table->is_finished == False)
	{
		pthread_mutex_unlock(&table->is_finished_mutex);
		pthread_mutex_lock(&table->fork[(i + side) % table->nb_philo]);
		print_action(table, Take_fork, i);
		return (True);
	}
	pthread_mutex_unlock(&table->is_finished_mutex);
	return (False);
}

t_bool	philo_eat(t_table *table, int i)
{
	pthread_mutex_lock(&table->is_finished_mutex);
	if (table->is_finished == False)
	{
		pthread_mutex_unlock(&table->is_finished_mutex);
		print_action(table, Eat, i);
		table->time_last_meal[i] = get_time_now();
		usleep(table->time_to_eat * 1000);
		pthread_mutex_unlock(&table->fork[i]);
		pthread_mutex_unlock(&table->fork[(i + 1) % table->nb_philo]);
		return (True);
	}
	pthread_mutex_unlock(&table->is_finished_mutex);
	return (False);
}

t_bool	philo_sleep(t_table *table, int i)
{
	pthread_mutex_lock(&table->is_finished_mutex);
	if (table->is_finished == False)
	{
		pthread_mutex_unlock(&table->is_finished_mutex);
		print_action(table, Sleep, i);
		usleep(table->time_to_sleep * 1000);
		return (True);
	}
	pthread_mutex_unlock(&table->is_finished_mutex);
	return (False);
}

t_bool	philo_think(t_table *table, int i)
{
	pthread_mutex_lock(&table->is_finished_mutex);
	if (table->is_finished == False)
	{
		pthread_mutex_unlock(&table->is_finished_mutex);
		print_action(table, Think, i);
		return (True);
	}
	pthread_mutex_unlock(&table->is_finished_mutex);
	return (False);
}
