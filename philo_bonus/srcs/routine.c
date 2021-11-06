/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/07 00:23:40 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* t_bool	check_end_simulation(t_table *table) */
/* { */
	/* return (read_protected_data(&table->no_one_died) == True */
		/* && read_protected_data(&table->nb_philo_ate_enough) != table->nb_philo); */
/* } */

static void	sync_philo(t_table *table, int i)
{
	(void)i;
	sem_wait(table->sync_start.start_all);
	sem_post(table->sync_start.start_all);
	/* if (i % 2 == 1) */
		/* increment_protected_data(&table->sync_start.odd_count); */
	/* if (i % 2 == 0) */
	/* { */
		/* pthread_mutex_lock(&table->sync_start.start_even); */
		/* pthread_mutex_unlock(&table->sync_start.start_even); */
	/* } */
}

static void	routine_loop(
			t_table *table, int i/* , enum e_side first, enum e_side second */)
{
	int	nb_time;

	nb_time = 0;
	while (/* check_end_simulation(table) ==  */True)
	{
		usleep(1000);
		/* if (philo_take_fork(table, i[> , first <]) == False) */
			/* break ; */
		if (philo_take_fork(table, i/* , second */) == False)
			break ;
		if (philo_eat(table, i) == False)
			break ;
		if (table->nb_time_each_philo_must_eat != -1)
		{
			++nb_time;
			if (nb_time == table->nb_time_each_philo_must_eat)
			{
				/* increment_protected_data(&table->nb_philo_ate_enough); */
				exit(EXIT_SUCCESS);
				break ;
			}
		}
		if (philo_sleep(table, i) == False)
			break ;
		if (philo_think(table, i) == False)
			break ;
	}
}

/* static void	init_sides( */
			/* int nb_philo, int i, enum e_side *first, enum e_side *second) */
/* { */
	/* if (nb_philo % 2 == 0 && i % 2) */
	/* { */
		/* *first = Right; */
		/* *second = Left; */
	/* } */
	/* else */
	/* { */
		/* *first = Left; */
		/* *second = Right; */
	/* } */
/* } */

void	routine(int i)
{
	t_table		*table;
	/* enum e_side	first; */
	/* enum e_side	second; */

	table = get_table();
	/* if (read_protected_data(&table->no_one_died) == True) */
		sync_philo(table, i);
	/* init_sides(table->nb_philo, i, &first, &second); */
	routine_loop(table, i /*, first, second */);
}
