/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:02:07 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/08 18:13:09 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destructor(void) __attribute__((destructor));

void	destructor(void)
{
	t_table	*table;

	table = get_table();
	free(table->watcher);
	free(table->time_last_meal);
	sem_destroy(table->sem_forks);
	sem_destroy(table->sem_write);
	sem_destroy(table->sem_stop);
	sem_destroy(table->sem_sync_start);
	sem_destroy(table->sem_eat);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_SYNC_START);
	sem_unlink(SEM_EAT);
}

t_table	*get_table(void)
{
	static t_table	table = {
		.time_start = 0,
		.nb_philo = 0,
		.time_to_die = 0,
		.time_to_eat = 0,
		.time_to_sleep = 0,
		.nb_time_each_philo_must_eat = 0,
		.watcher = NULL,
		.time_last_meal = NULL,
		.nb_philo_ate_enough.val = 0,
		.no_one_died.val = True
	};

	return (&table);
}

int	main(int ac, char **av)
{
	t_table	*table;
	int		ret;

	table = get_table();
	ret = EXIT_SUCCESS;
	if (check_and_parse(ac, av, table) == False)
		return (EXIT_FAILURE);
	if (run_philo(table) == False)
		ret = EXIT_FAILURE;
	return (ret);
}
