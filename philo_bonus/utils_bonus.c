/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:28:21 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/19 18:46:44 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

int	check_meals(t_philo *philo)
{
	sem_wait(philo->data->meals_check);
	if (philo->meals == philo->data->meals_req)
	{
		sem_post(philo->data->meals_check);
		sem_post(philo->data->meals);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		return (1);
	}
	sem_post(philo->data->meals_check);
	return (0);
}

void	thinking(t_philo *philo)
{
	ph_print(philo, 4);
}
