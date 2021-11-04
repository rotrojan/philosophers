/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:58:03 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/04 00:30:25 by rotrojan         ###   ########.fr       */
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

	sem_wait(table->sem_write);
	printf("%6ld %d %s\n", get_time_now() - get_table()->time_start,
		index + 1, error_msg[action]);
	sem_post(table->sem_write);
}

/* t_bool	philo_take_fork(t_table *table, int i, enum e_side side) */
/* { */
	/* t_bool	ret; */
	

	/* return (ret); */
/* } */

t_bool	philo_eat(t_table *table, int i, long int *time_of_death)
{
	sem_wait(table->forks);
	print_action(table, Take_fork, i);
	sem_wait(table->forks);
	print_action(table, Take_fork, i);
	*time_of_death = get_time_now();
	print_action(table, Eat, i);
	msleep(table->time_to_eat, *time_of_death);
	sem_post(table->forks);
	sem_post(table->forks);
	return (True);
}

t_bool	philo_sleep(t_table *table, int i, long int *time_of_death)
{
	t_bool	ret;

	ret = True;
	print_action(table, Sleep, i);
	msleep(table->time_to_sleep, *time_of_death);
	return (ret);
}

t_bool	philo_think(t_table *table, int i, long int *time_of_death)
{
	t_bool	ret;

	ret = True;
	(void)time_of_death;
	if (ret == True)
		print_action(table, Think, i);
	return (ret);
}
