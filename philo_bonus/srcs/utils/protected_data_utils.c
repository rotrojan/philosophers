/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_data_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:10:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/11/08 18:47:53 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	read_protected_data(t_protected_data *data)
{
	int	ret;

	sem_wait(data->sem);
	ret = data->val;
	sem_post(data->sem);
	return (ret);
}

void	write_protected_data(t_protected_data *data, int val)
{
	sem_wait(data->sem);
	data->val = val;
	sem_post(data->sem);
}

void	increment_protected_data(t_protected_data *data)
{
	sem_wait(data->sem);
	++data->val;
	sem_post(data->sem);
}
