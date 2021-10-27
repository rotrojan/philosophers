/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:02:07 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/27 23:13:20 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destructor(void) __attribute__((destructor));

void	destructor(void)
{
	t_table	*table;
	int		i;

	table = get_table();
	i = 0;
	free(table->philo);
	free(table->time_last_meal);
	free(table->fork);
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
		.philo = NULL,
		.time_last_meal = 0,
		.fork = NULL,
		.is_finished = False
	};

	return (&table);
}

int	main(int ac, char **av)
{
	t_table	*table;
	int		ret;
	int		i;

	table = get_table();
	ret = EXIT_SUCCESS;
	if (check_and_parse(ac, av, table) == False)
		return (EXIT_FAILURE);
	if (run_philo(table) == False)
		ret = EXIT_FAILURE;
	i = 0;
	while (i < table->nb_philo)
		pthread_mutex_destroy(&table->fork[i++]);
	pthread_mutex_destroy(&table->write);
	return (ret);
}
