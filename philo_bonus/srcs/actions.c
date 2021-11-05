/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:58:03 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/05 03:27:47 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_end_simulation(t_table *table, long int time_of_death, int index)
{
	if (get_time_now() >= time_of_death)
	{
		print_action(table, Die, index);
		/* kill(0, SIGINT); */
		exit(EXIT_SUCCESS);
		/* return (False); */
	}
	return (True);
}

void	print_action(t_table *table, enum e_action action, int index)
{
	char const		*error_msg[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	sem_wait(table->sem_write);
	printf("%6ld %d %s\n", get_time_now() - get_table()->time_start,
		index + 1, error_msg[action]);
	sem_post(table->sem_write);
}

t_bool	philo_eat(t_table *table, int i, long int *time_of_death)
{
	t_bool	ret;

	ret = check_end_simulation(table, *time_of_death, i);
	if (ret == True)
	{
		sem_wait(table->forks);
		print_action(table, Take_fork, i);
	}
	ret = check_end_simulation(table, *time_of_death, i);
	if (ret == True)
	{
		sem_wait(table->forks);
		print_action(table, Take_fork, i);
	}
	ret = check_end_simulation(table, *time_of_death, i);
	if (ret == True)
	{
		*time_of_death = get_time_now() + table->time_to_die;
		print_action(table, Eat, i);
		msleep(table->time_to_eat, *time_of_death);
		sem_post(table->forks);
		sem_post(table->forks);
	}
	return (True);
}

t_bool	philo_sleep(t_table *table, int i, long int *time_of_death)
{
	t_bool	ret;

	ret = check_end_simulation(table, *time_of_death, i);
	if (ret == True)
	{
		print_action(table, Sleep, i);
		msleep(table->time_to_sleep, *time_of_death);
	}
	return (ret);
}

t_bool	philo_think(t_table *table, int i, long int *time_of_death)
{
	t_bool	ret;

	ret = check_end_simulation(table, *time_of_death, i);
	if (ret == True)
		print_action(table, Think, i);
	return (ret);
}
