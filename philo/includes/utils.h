/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 23:25:00 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/27 22:58:04 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

int			ft_atoi(char const *str);
long long	ft_atoll(char const *str);
void		ft_putstr_fd(char const *str, int fd);
size_t		ft_strlen(char const *str);
t_bool		print_error(char *const error_msg);
long int	get_time_now(void);

#endif
