/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:57:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/04 00:04:38 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	run_philo(t_table *table)
{
	int		i;
	pid_t	pid;

	table->time_start = get_time_now();
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("stop");
	table->forks = sem_open("forks", O_CREAT, 0744, table->nb_philo);
	table->sem_write = sem_open("write", O_CREAT, 0744, 1);
	table->sem_stop = sem_open("stop", O_CREAT, 0744, 1);
	i = 0;
	while (i < table->nb_philo)
	{
		pid = fork();
		if (pid == -1)
			return (print_error(FORK_ERR_MSG));
		if (pid == 0)
			break ;
		++i;
	}
	if (pid == 0)
		routine(i, table);
	else
	{
		i = 0;
		while (i < table->nb_philo)
		{
			waitpid(0, NULL, 0);
			++i;
		}
	}
	return (True);
}
