/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:58:03 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/07 00:51:12 by rotrojan         ###   ########.fr       */
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

t_bool	philo_take_fork(t_table *table, int i/* , enum e_side side */)
{
	t_bool	ret;

	ret = True;
	/* while (True) */
	/* { */
		/* if (read_protected_data(&table->fork[(i + side) % table->nb_philo]) */
			/* == True || check_end_simulation(table) == False) */
			/* break ; */
		/* usleep(100); */
	/* } */
	/* ret = check_end_simulation(table); */
	sem_wait(table->sem_stop);
	/* if (ret == True) */
		/* write_protected_data(&table->fork[(i + side) % table->nb_philo], False); */
	/* ret = check_end_simulation(table); */
	/* if (ret == True) */
	sem_wait(table->sem_forks);
		print_action(table, Take_fork, i);
	sem_wait(table->sem_forks);
		print_action(table, Take_fork, i);
	/* while (table->nb_philo == 1) */
	/* { */
		/* if (read_protected_data(&table->no_one_died) == False) */
			/* return (False); */
		/* usleep(100); */
	/* } */
	sem_post(table->sem_stop);
	return (ret);
}

t_bool	philo_eat(t_table *table, int i)
{
	t_bool	ret;

	ret = True;
	/* ret = check_end_simulation(table); */
	/* sem_wait(table->sem_stop); */
	/* if (ret == True) */
		print_action(table, Eat, i);
	sem_post(table->sem_eat);
	/* ret = check_end_simulation(table); */
	/* ret = check_end_simulation(table); */
	/* if (ret == True) */
	/* sem_post(table->sem_stop); */
		msleep(table->time_to_eat);
	sem_post(table->sem_forks);
	sem_post(table->sem_forks);
	/* write_protected_data(&table->fork[i], True); */
	/* write_protected_data(&table->fork[(i + 1) % table->nb_philo], True); */
	return (ret);
}

t_bool	philo_sleep(t_table *table, int i)
{
	t_bool	ret;

	ret = True;
	/* sem_wait(table->sem_stop); */
	/* ret = check_end_simulation(table); */
	/* if (ret == True) */
		print_action(table, Sleep, i);
	/* ret = read_protected_data(&table->no_one_died); */
	/* if (ret == True) */
	/* sem_post(table->sem_stop); */
		msleep(table->time_to_sleep);
	return (ret);
}

t_bool	philo_think(t_table *table, int i)
{
	t_bool	ret;

	ret = True;
	/* sem_wait(table->sem_stop); */
	/* ret = check_end_simulation(table); */
	/* if (ret == True) */
		print_action(table, Think, i);
	/* sem_post(table->sem_stop); */
	usleep(300);
	return (ret);
}
