/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/05 03:10:29 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine_loop(t_table *table, int i, long int *time_of_death)
{
	int	nb_time;

	nb_time = 0;
	while (True)
	{
		if (get_time_now() >= *time_of_death)
			return ;
		if (philo_eat(table, i, time_of_death) == False)
			break ;
		/* if (table->nb_time_each_philo_must_eat != -1) */
		/* { */
			/* ++nb_time; */
			/* if (nb_time == table->nb_time_each_philo_must_eat) */
			/* { */
				/* increment_protected_data(&table->nb_philo_ate_enough); */
				/* break ; */
			/* } */
		/* } */
		if (philo_sleep(table, i, time_of_death) == False)
			break ;
		if (philo_think(table, i, time_of_death) == False)
			break ;
		usleep(100);
	}
}

void	routine(int index, t_table *table)
{
	long int	time_of_death;

	time_of_death = get_time_now() + table->time_to_die;
	routine_loop(table, index, &time_of_death);
}
