/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 21:40:04 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/26 19:57:29 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "utils.h"
# include "ft_bool.h"

enum	e_action
{
	Take_fork,
	Eat,
	Sleep,
	Think,
	Die
};

typedef struct s_table
{
	long int		time_start;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_each_philo_must_eat;
	pthread_t		*philo;
	long int		*time_last_meal;
	pthread_mutex_t	*fork;
	t_bool			is_finished;
}	t_table;

t_table	*get_table(void);
t_bool	check_and_parse(int ac, char **av, t_table *table);
t_bool	run_philo(t_table *table);

#endif
