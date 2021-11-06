/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/07 00:37:59 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
		kill(table->pid[i++], SIGINT);
}

static t_bool	join_threads(t_table *table)
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

static void	sync_monitor(t_table *table)
{
	sem_post(table->sync_start.start_all);
	/* while (read_protected_data(&table->sync_start.odd_count) */
		/* != table->nb_philo / 2) */
		/* usleep(50); */
	/* pthread_mutex_unlock(&table->sync_start.start_even); */
}

static t_bool	end_simulation(t_table *table, int i)
{
	/* if (read_protected_data(&table->no_one_died) == False) */
		print_action(table, Die, i);
	kill_all(table);
	return (join_threads(table));
}

t_bool	monitor(t_table *table)
{
	int		i;
	t_bool	ret;

	ret = True;
	sync_monitor(table);
	while (/* check_end_simulation(table) */table->no_one_died == True)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (get_time_now() - table->time_last_meal[i] >= table->time_to_die)
			{
				/* printf("pouetpouet\n"); */
				table->no_one_died = False;
				/* sem_wait(table->sem_stop); */
				break ;
			}
			/* if (read_protected_data(&table->nb_philo_ate_enough) */
				/* == table->nb_philo) */
				/* break ; */
			++i;
		}
	}
	end_simulation(table, i);
	return (ret);
}
