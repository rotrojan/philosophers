/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bigo <rotrojan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 22:34:25 by bigo              #+#    #+#             */
/*   Updated: 2021/10/27 22:35:26 by bigo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	print_error(char *const error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	return (False);
}
