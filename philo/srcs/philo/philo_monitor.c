/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/28 02:09:00 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	monitor(t_table *table)
{
	int		i;
	t_bool	ret;

	ret = True;
	while (table->is_finished == False)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (get_time_now() - table->time_last_meal[i]
				>= table->time_to_die)
			{
				pthread_mutex_lock(&table->is_finished_mutex);
				table->is_finished = True;
				pthread_mutex_unlock(&table->is_finished_mutex);
				print_action(table, Die, i);
				if (join_threads(table) == False)
					ret = False;
				break ;
			}
			++i;
		}
	}
	return (ret);
}
