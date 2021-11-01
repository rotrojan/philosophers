/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 21:40:04 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/01 20:58:07 by bigo             ###   ########.fr       */
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

# define ARGS_NB_ERR_MSG "Error: wrong number of arguments\n"
# define NOT_NUM_ARG_ERR_MSG "Error: the arguments must be numeric\n"
# define ARG_NOT_POS_ERR_MSG "Error: the arguments must be strictly positive\n"
# define OVERFLOW_ERR_MSG "Error: the arguments must in the int range\n"

# define MALLOC_ERR_MSG "Error: memory allocation failed\n"
# define MUTEX_ERR_MSG "Error: mutex initialization failed\n"
# define THREAD_ERR_MSG "Error: thread creation failed\n"
# define JOIN_ERR_MSG "Error: thread jonction failed\n"

typedef enum e_bool
{
	False,
	True
}	t_bool;

enum	e_action
{
	Take_fork,
	Eat,
	Sleep,
	Think,
	Die
};

enum	e_side
{
	Left,
	Right
};

typedef struct s_protected_data
{
	long int		val;
	pthread_mutex_t	mutex;
}	t_protected_data;

typedef struct s_sync_start
{
	pthread_mutex_t		start_all;
	pthread_mutex_t		start_even;
	t_protected_data	odd_count;
}	t_sync_start;

typedef struct s_table
{
	long int			time_start;
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_time_each_philo_must_eat;
	pthread_t			*philo;
	t_protected_data	*time_last_meal;
	t_protected_data	*fork;
	t_protected_data	no_one_died;
	pthread_mutex_t		write_mutex;
	t_sync_start		sync_start;
	t_protected_data	nb_philo_ate_enough;
}	t_table;

/*
** philo_main.c
*/

t_table		*get_table(void);

/*
** philo_parsing.c
*/

t_bool		check_and_parse(int ac, char **av, t_table *table);

/*
** monitor.c
*/

t_bool		monitor(t_table *table);

/*
** run_philo.c
*/

t_bool		run_philo(t_table *table);
t_bool		join_threads(t_table *table);

/*
** routine.c
*/

t_bool		check_end_simulation(t_table *table);
void		*routine(void *index);

/*
** actions.c
*/

void		print_action(t_table *table, enum e_action action, int index);
t_bool		philo_take_fork(t_table *table, int i, enum e_side side);
t_bool		philo_eat(t_table *table, int i);
t_bool		philo_sleep(t_table *table, int i);
t_bool		philo_think(t_table *table, int i);

/*
** utils.c
*/

int			ft_atoi(char const *str);
long long	ft_atoll(char const *str);
void		ft_putstr_fd(char const *str, int fd);
size_t		ft_strlen(char const *str);
t_bool		print_error(char *const error_msg);
long int	get_time_now(void);
long int	read_protected_data(t_protected_data *data);
void		write_protected_data(t_protected_data *data, long int val);
void		increment_protected_data(t_protected_data *data);
void		msleep(int msec);

#endif
