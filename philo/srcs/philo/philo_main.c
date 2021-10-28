/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:02:07 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/28 17:50:18 by rotrojan         ###   ########.fr       */
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
		.is_finished.val = False
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
	i = 0;
	while (i < table->nb_philo)
		pthread_mutex_destroy(&table->time_last_meal[i++].mutex);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->is_finished.mutex);
	return (ret);
}
