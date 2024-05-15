/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:21:00 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/17 16:10:28 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	thinking(t_philo *philo)
{
	if (!check_end(philo))
		ph_print(philo, 4);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (!check_end(philo))
		ph_print(philo, 3);
	drop_forks(philo);
	ms_sleep(philo->data->sleep_time, philo, 0);
	return (0);
}

int	eating(t_philo *philo)
{
	if (philo->i % 2 == 0 && philo->meals == 0)
	{
		thinking(philo);
		ms_sleep(philo->data->eat_time / 2, philo, 0);
	}
	check_forks(philo);
	take_forks(philo);
	if (!check_end(philo))
		ph_print(philo, 1);
	ms_sleep(philo->data->eat_time, philo, 1);
	pthread_mutex_lock(&philo->data->meals_m);
	philo->meals++;
	pthread_mutex_unlock(&philo->data->meals_m);
	return (0);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!check_end(philo))
	{
		eating(philo);
		if (check_meals(philo))
		{
			drop_forks(philo);
			return (NULL);
		}
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	init_threads(t_data *data, t_philo *philos)
{
	int			i;
	t_philo		*t;
	pthread_t	monitor;

	i = -1;
	while (++i < data->ph_num)
	{
		t = &philos[i];
		pthread_create(&t->t, NULL, routine, &philos[i]);
	}
	pthread_create(&monitor, NULL, monitoring, philos);
	i = -1;
	while (++i < data->ph_num)
	{
		t = &philos[i];
		pthread_join(t->t, NULL);
	}
	pthread_join(monitor, NULL);
}
