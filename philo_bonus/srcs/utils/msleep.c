/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:48:38 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/08 19:10:08 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	msleep(int msec)
{
	long int	start_time;
	t_table		*table;

	start_time = get_time_now();
	table = get_table();
	while (get_time_now() - start_time < msec)
		usleep(100);
}
