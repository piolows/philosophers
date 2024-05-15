/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:28:21 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/22 15:11:19 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_meals(t_philo *philo)
{
	if (philo->data->meals_req == -1)
		return (0);
	pthread_mutex_lock(&philo->data->meals_m);
	if (philo->meals >= philo->data->meals_req)
	{
		pthread_mutex_unlock(&philo->data->meals_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meals_m);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
