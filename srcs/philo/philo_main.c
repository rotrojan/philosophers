/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:02:07 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/26 19:50:28 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destructor(void) __attribute__((destructor));

void	destructor(void)
{
	t_table	*table;

	table = get_table();
	free(table->philo);
	free(table->fork);
}

t_table	*get_table()
{
	static	t_table	table = {
		.time_start = 0,
		.nb_philo = 4,
		.time_to_die = 100,
		.time_to_eat = 100,
		.time_to_sleep = 100,
		.nb_time_each_philo_must_eat = -1,
		.philo = NULL,
		.time_last_meal = 0,
		.fork = NULL,
		.is_finished = False
	};

	 return (&table);
}

int	main(int ac, char **av)
{
	t_table			*table;

	table = get_table();
	(void)(ac && av);
	/* if (check_and_parse(ac, av, table) == False) */
		/* return (EXIT_FAILURE); */
	run_philo(table);
	return (0);
}
