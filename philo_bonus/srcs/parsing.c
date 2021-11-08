/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bigo <rotrojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:18:20 by bigo              #+#    #+#             */
/*   Updated: 2021/10/27 18:10:32 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	str_is_numeric(char const *str)
{
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (False);
		++str;
	}
	return (True);
}

t_bool	check_and_parse_single_arg(char const *arg, int *const data)
{
	long long int	buffer;

	if (str_is_numeric(arg) == False)
		return (print_error(NOT_NUM_ARG_ERR_MSG));
	buffer = ft_atoll(arg);
	if (buffer <= 0)
		return (print_error(ARG_NOT_POS_ERR_MSG));
	else if (ft_atoi(arg) != buffer)
		return (print_error(OVERFLOW_ERR_MSG));
	*data = buffer;
	return (True);
}

t_bool	check_and_parse(int ac, char **av, t_table *table)
{
	int			i;
	int *const	data[] = {
		&table->nb_philo, &table->time_to_die,
		&table->time_to_eat, &table->time_to_sleep,
		&table->nb_time_each_philo_must_eat
	};

	if (ac < 5 || ac > 6)
		return (print_error(ARGS_NB_ERR_MSG));
	if (ac == 5)
		table->nb_time_each_philo_must_eat = -1;
	i = 1;
	while (av[i] != NULL)
	{
		if (check_and_parse_single_arg(av[i], data[i - 1]) == False)
			return (False);
		++i;
	}
	return (True);
}
