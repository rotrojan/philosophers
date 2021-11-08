/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 21:40:04 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/08 21:13:44 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define ARGS_NB_ERR_MSG "Error: wrong number of arguments\n"
# define NOT_NUM_ARG_ERR_MSG "Error: the arguments must be numeric\n"
# define ARG_NOT_POS_ERR_MSG "Error: the arguments must be strictly positive\n"
# define OVERFLOW_ERR_MSG "Error: the arguments must in the int range\n"

# define MALLOC_ERR_MSG "Error: memory allocation failed\n"
# define THREAD_ERR_MSG "Error: thread creation failed\n"
# define JOIN_ERR_MSG "Error: thread jonction failed\n"
# define SEM_OPEN_ERR_MSG "Error: semaphore creation failed\n"
# define FORK_ERR_MSG "Error: processus creation failed\n"

# define SEM_FORKS "/sem_forks"
# define SEM_WRITE "/sem_write"
# define SEM_STOP "/set_stop"
# define SEM_SYNC_START "/sem_sync_start"
# define SEM_EAT "/sem_eat"
# define SEM_NO_ONE_DIED "/sem_mo_one_died"
# define SEM_NB_PHILO_ATE_ENOUGH "/sem_nb_philo_ate_enough"
# define SEM_LAST_MEAL "/sem_last_meal"

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
};

typedef struct s_protected_data
{
	int			val;
	sem_t		*sem;
}	t_protected_data;

typedef struct s_table
{
	long int			time_start;
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_time_each_philo_must_eat;
	pthread_t			*watcher;
	pid_t				*pid;
	sem_t				*sem_forks;
	sem_t				*sem_stop;
	sem_t				*sem_write;
	sem_t				*sem_eat;
	sem_t				*sem_last_meal;
	long int			*time_last_meal;
	sem_t				*sem_sync_start;
	t_protected_data	nb_philo_ate_enough;
	t_protected_data	no_one_died;
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

void		*watcher(long int *time_last_meal);
t_bool		join_threads(t_table *table);
void		monitor(t_table *table);
void		kill_all(t_table *table);

/*
** run_philo.c
*/

t_bool		run_philo(t_table *table);

/*
** open_semaphores.c
*/

t_bool		open_semaphores(t_table *table);

/*
** routine.c
*/

t_bool		check_end_simulation(t_table *table);
void		routine(int i);

/*
** actions.c
*/

void		print_action(t_table *table, enum e_action action, int index);
void		philo_take_forks(t_table *table, int i);
void		philo_eat(t_table *table, int i);
void		philo_sleep(t_table *table, int i);
void		philo_think(t_table *table, int i);

/*
** utils.c
*/

int			ft_atoi(char const *str);
long long	ft_atoll(char const *str);
void		ft_putstr_fd(char const *str, int fd);
size_t		ft_strlen(char const *str);
t_bool		print_error(char *const error_msg);
long int	get_time_now(void);
int			read_protected_data(t_protected_data *data);
void		write_protected_data(t_protected_data *data, int val);
void		increment_protected_data(t_protected_data *data);
void		msleep(int msec);

#endif
