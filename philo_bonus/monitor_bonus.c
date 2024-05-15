/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:19:24 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/19 18:45:43 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_end(t_philo *philo)
{
	sem_wait(philo->data->end_s);
	if ((philo->end) == 1)
	{
		sem_post(philo->data->end_s);
		return (1);
	}
	sem_post(philo->data->end_s);
	return (0);
}

int	check_time(t_philo *philo)
{
	sem_wait(philo->data->start_s);
	if (get_time() - philo->start >= (size_t)philo->data->death_time)
	{
		sem_post(philo->data->start_s);
		return (1);
	}
	sem_post(philo->data->start_s);
	return (0);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = -1;
	if (check_end(philo))
		return (0);
	if (check_time(philo))
	{
		sem_wait(philo->data->write_s);
		printf(RESET "%ld\t", get_time() - philo->data->timer);
		printf(RED BOLD "%d died\n" RESET, philo->i);
		while (++i < philo->data->ph_num)
			sem_post(philo->data->terminate);
		return (1);
	}
	return (0);
}

void	*monitor(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		if (check_end(philo))
			break ;
		if (check_death(philo))
			break ;
		sem_wait(philo->data->meals_check);
		if (philo->meals == philo->data->meals_req)
		{
			sem_post(philo->data->meals_check);
			break ;
		}
		sem_post(philo->data->meals_check);
	}
	return (NULL);
}

void	*checkterm(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	sem_wait(philo->data->terminate);
	sem_post(philo->data->meals);
	sem_wait(philo->data->end_s);
	philo->end = 1;
	sem_post(philo->data->end_s);
	return (NULL);
}
