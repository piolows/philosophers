/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:22:45 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/01 21:16:43 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	*(philo->rf) = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	*(philo->lf) = 0;
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

int	take_forks(t_philo *philo)
{
	int	f;

	f = 0;
	if (!check_rf(philo))
	{
		take_r_fork(philo);
		f = 1;
	}
	else if (!check_lf(philo))
	{
		take_l_fork(philo);
		f = 2;
	}
	if (f == 1)
		take_l_fork(philo);
	else if (f == 2)
		take_r_fork(philo);
	return (0);
}

int	take_r_fork(t_philo *philo)
{
	while (!check_end(philo))
	{
		if (check_rf(philo))
			usleep(100);
		else
			break ;
	}
	pthread_mutex_lock(philo->r_fork);
	*(philo->rf) = 1;
	pthread_mutex_unlock(philo->r_fork);
	if (!check_end(philo))
		ph_print(philo, 2);
	return (0);
}

int	take_l_fork(t_philo *philo)
{
	while (!check_end(philo))
	{
		if (check_lf(philo))
			usleep(100);
		else
			break ;
	}
	pthread_mutex_lock(philo->l_fork);
	*(philo->lf) = 1;
	pthread_mutex_unlock(philo->l_fork);
	if (!check_end(philo))
		ph_print(philo, 2);
	return (0);
}
