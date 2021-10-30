/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/30 12:58:05 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	monitor(t_table *table)
{
	int		i;
	t_bool	ret;

	ret = True;
	while (read_protected_data(&table->no_one_died) == True)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (get_time_now() - read_protected_data(&table->time_last_meal[i])
				>= table->time_to_die)
			{
				write_protected_data(&table->no_one_died, False);
				print_action(table, Die, i);
				if (join_threads(table) == False)
					ret = False;
				break ;
			}
			++i;
		}
		usleep(100);
	}
	return (ret);
}
