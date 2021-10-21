/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 21:35:58 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/22 01:09:45 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	print_error_and_return(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	return (False);
}

t_bool	str_is_numeric(char const *str)
{
	while (*str != '\0')
	{
		if (*str < '0' && *str > '9')
			return (False);
		++str;
	}
	return (True);
}

t_bool	check_and_parse(int ac, char **av, t_table *table)
{
	int	i;
	int	*args[] = { &table->nb_philo, &table->time_to_die, &table->time_to_eat,
		&table->time_to_sleep, &table->nb_time_each_philo_must_eat };

	if (ac < 5 || ac > 6)
		return (print_error_and_return("Wrong number of arguments\n"));
	i = 1;
	while (av[i] != NULL)
	{
		if (str_is_numeric(av[i]) == False)
			return (print_error_and_return("The arguments must be numeric\n"));
		(*args)[i - 1] = ft_atoi(av[i]);
		if ((*args)[i - 1] <= 0)
			return (print_error_and_return(
					"The arguments must be strictly positive\n"));
		else if (ft_atoll(av[i]) != (*args)[i - 1])
			return (print_error_and_return(
					"The arguments must in the int range\n"));
		++i;
	}
	return (True);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (check_and_parse(ac, av, &table) == False)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
