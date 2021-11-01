/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:02:07 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/01 20:31:42 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destructor(void) __attribute__((destructor));

void	destructor(void)
{
	t_table	*table;

	table = get_table();
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
		.time_last_meal = NULL,
		.fork = NULL,
		.no_one_died.val = True,
		.sync_start.odd_count.val = 0,
		.nb_philo_ate_enough.val = 0
	};

	return (&table);
}

t_bool	destroy_mutexes(t_table *table)
{
	t_bool	ret;
	int		i;

	ret = True;
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_destroy(&table->fork[i].mutex) != 0)
			ret = False;
		if (pthread_mutex_destroy(&table->time_last_meal[i].mutex) != 0)
			ret = False;
		++i;
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->no_one_died.mutex);
	return (ret);
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
	if (destroy_mutexes(table) == False)
		ret = EXIT_FAILURE;
	return (ret);
}
