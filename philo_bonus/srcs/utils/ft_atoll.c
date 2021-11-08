/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rotrojan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:51:21 by rotrojan          #+#    #+#             */
/*   Updated: 2021/10/21 23:37:12 by rotrojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_atoll(char const *str)
{
	long long	result;
	int			is_negative;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		is_negative = -1;
	else
		is_negative = 1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0;
	while (*str >= '0' && *str <= '9' && *str)
		result = result * 10 + *(str++) - '0';
	return (result * is_negative);
}
