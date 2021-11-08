/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/08 19:47:25 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*watcher(long int *time_last_meal)
{
	t_table		*table;
	int			nb_time;

	table = get_table();
	nb_time = 0;
	while (check_end_simulation(table) == True)
	{
		sem_wait(table->sem_eat);
		*time_last_meal = get_time_now();
		++nb_time;
		if (nb_time == table->nb_time_each_philo_must_eat)
			increment_protected_data(&table->nb_philo_ate_enough);
	}
	return (NULL);
}

void	kill_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
		kill(table->pid[i++], SIGINT);
}

t_bool	join_threads(t_table *table)
{
	int		i;
	t_bool	ret;

	i = 0;
	ret = True;
	while (i < table->nb_philo)
	{
		sem_post(table->sem_eat);
		++i;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->watcher[i], NULL) != 0)
			ret = False;
		++i;
	}
	return (ret);
}

static t_bool	end_simulation(t_table *table, int i)
{
	if (read_protected_data(&table->no_one_died) == False)
		printf("%6ld %d %s\n", get_time_now() - get_table()->time_start, i + 1,
			"died");
	kill_all(table);
	return (join_threads(table));
}

void	monitor(t_table *table)
{
	int		i;

	sem_post(table->sem_sync_start);
	while (check_end_simulation(table) == True)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (get_time_now() - table->time_last_meal[i] >= table->time_to_die)
			{
				sem_wait(table->sem_write);
				write_protected_data(&table->no_one_died, False);
				break ;
			}
			if (read_protected_data(&table->nb_philo_ate_enough)
				== table->nb_philo)
			{
				sem_wait(table->sem_write);
				break ;
			}
			++i;
		}
		usleep(50);
	}
	end_simulation(table, i);
}
