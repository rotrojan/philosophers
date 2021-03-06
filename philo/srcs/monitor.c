/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/06 18:59:27 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	join_threads(t_table *table)
{
	int		i;
	t_bool	ret;

	i = 0;
	ret = True;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->philo[i], NULL) != 0)
			ret = False;
		++i;
	}
	return (ret);
}

static void	sync_monitor(t_table *table)
{
	pthread_mutex_unlock(&table->sync_start.start_all);
	while (read_protected_data(&table->sync_start.odd_count)
		!= table->nb_philo / 2)
		usleep(50);
	pthread_mutex_unlock(&table->sync_start.start_even);
}

static t_bool	end_simulation(t_table *table, int i)
{
	if (read_protected_data(&table->no_one_died) == False)
		print_action(table, Die, i);
	return (join_threads(table));
}

t_bool	monitor(t_table *table)
{
	int		i;
	t_bool	ret;

	ret = True;
	sync_monitor(table);
	while (check_end_simulation(table) == True)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (get_time_now() - table->time_last_meal[i] >= table->time_to_die)
			{
				write_protected_data(&table->no_one_died, False);
				break ;
			}
			if (read_protected_data(&table->nb_philo_ate_enough)
				== table->nb_philo)
				break ;
			++i;
		}
		usleep(100);
	}
	end_simulation(table, i);
	return (ret);
}
