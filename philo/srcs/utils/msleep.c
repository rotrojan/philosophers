/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:48:38 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/30 12:48:12 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(int msec)
{
	long int	start_time;
	t_table		*table;

	start_time = get_time_now();
	table = get_table();
	while (get_time_now() - start_time < msec)
	{
		if (read_protected_data(&table->no_one_died) == False)
			break ;
		usleep(100);
	}
}
