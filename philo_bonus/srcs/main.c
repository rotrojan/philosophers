/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:02:07 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/04 00:19:00 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destructor(void) __attribute__((destructor));

void	destructor(void)
{
	t_table	*table;

	table = get_table();
	/* free(table->philo); */
	/* free(table->time_last_meal); */
	/* free(table->fork); */
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
	/* if (destroy_mutexes(table) == False) */
		/* ret = EXIT_FAILURE; */
	return (ret);
}
