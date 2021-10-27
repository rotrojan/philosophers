/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/27 23:08:45 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *index)
{
	t_table	*table;
	int		i;

	table = get_table();
	i = *(int *)index;
	free(index);
	while (table->is_finished == False)
	{
		if (philo_take_fork(table, i, Left) == False)
			break ;
		if (philo_take_fork(table, i, Right) == False)
			break ;
		if (philo_eat(table, i) == False)
			break ;
		if (philo_sleep(table, i) == False)
			break ;
		if (philo_think(table, i) == False)
			break ;
	}
	return (NULL);
}
