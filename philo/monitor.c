/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:19:24 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/17 16:36:17 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start_m);
	if (get_time() - philo->start >= (size_t)philo->data->death_time)
	{
		pthread_mutex_unlock(&philo->data->start_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->start_m);
	return (0);
}

int	set_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_m);
	*(philo->end) = 1;
	pthread_mutex_unlock(&philo->data->end_m);
	return (0);
}

int	check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_m);
	if (*(philo->end) == 1)
	{
		pthread_mutex_unlock(&philo->data->end_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->end_m);
	return (0);
}

int	check_death(t_philo *philo)
{
	if (check_end(philo))
		return (1);
	if (check_time(philo))
	{
		set_end(philo);
		pthread_mutex_lock(&philo->data->write);
		printf("%ld\t", get_time() - philo->data->timer);
		printf(RED BOLD "%d died\n" RESET, philo->i);
		pthread_mutex_unlock(&philo->data->write);
		return (1);
	}
	return (0);
}

void	*monitoring(void *p)
{
	int		i;
	int		m;
	t_philo	*philos;
	t_philo	*philo;

	philos = (t_philo *)p;
	while (1)
	{
		i = -1;
		m = 0;
		while (++i < philos->data->ph_num)
		{
			philo = &philos[i];
			if (check_death(philo))
				break ;
			if (philo->data->meals_req != -1 && check_meals(philo))
				m++;
		}
		if (philo->data->meals_req != -1 && m == philos->data->ph_num)
			set_end(philo);
		if (check_end(philo))
			break ;
	}
	return (NULL);
}
