/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:15:47 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/01 21:16:55 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_rf(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (*(philo->rf) == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	check_lf(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (*(philo->lf) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

int	check_forks(t_philo *philo)
{
	while (!check_end(philo))
	{
		if (check_rf(philo) && check_lf(philo) && !check_end(philo))
			usleep(100);
		else
			break ;
	}
	return (0);
}
