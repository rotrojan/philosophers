/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/27 23:08:20 by bigo             ###   ########.fr       */
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
				table->is_finished = True;
				print_action(Die, i);
				if (join_threads(table) == False)
					ret = False;
				break ;
			}
			++i;
		}
	}
	return (ret);
}
