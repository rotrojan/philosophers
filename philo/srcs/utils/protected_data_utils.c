/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_data_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:10:51 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/28 18:23:50 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	read_protected_data(t_protected_data *data)
{
	long int	ret;

	pthread_mutex_lock(&data->mutex);
	ret = data->val;
	pthread_mutex_unlock(&data->mutex);
	return (ret);
}

void	write_protected_data(t_protected_data *data, long int val)
{
	pthread_mutex_lock(&data->mutex);
	data->val = val;
	pthread_mutex_unlock(&data->mutex);
}
