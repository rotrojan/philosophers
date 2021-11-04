/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:48:38 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/03 22:18:27 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msleep(int msec, long int time_of_death)
{
	long int	start_time;
	t_table		*table;

	start_time = get_time_now();
	table = get_table();
	while (get_time_now() - start_time < msec)
	{
		if (get_time_now() >= time_of_death)
			break ;
		usleep(100);
	}
}
