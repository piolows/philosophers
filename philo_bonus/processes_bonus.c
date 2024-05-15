/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:41:08 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/19 18:46:27 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	sleeping(t_philo *philo)
{
	ph_print(philo, 3);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	ms_sleep(philo->data->sleep_time, philo, 0);
}

void	eating(t_philo *philo)
{
	if (philo->i % 2 == 0 && philo->meals == 0)
	{
		thinking(philo);
		ms_sleep(philo->data->eat_time / 2, philo, 0);
	}
	sem_wait(philo->data->forks);
	ph_print(philo, 2);
	sem_wait(philo->data->forks);
	ph_print(philo, 2);
	ph_print(philo, 1);
	sem_wait(philo->data->meals_check);
	philo->meals++;
	sem_post(philo->data->meals_check);
	ms_sleep(philo->data->eat_time, philo, 1);
}

int	routine(t_philo *philo)
{
	while (!check_end(philo))
	{
		eating(philo);
		if (check_meals(philo))
			return (0);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}

void	child_process(t_philo *philo)
{
	pthread_create(&philo->mon, NULL, monitor, philo);
	pthread_create(&philo->term, NULL, checkterm, philo);
	routine(philo);
	pthread_join(philo->mon, NULL);
	pthread_join(philo->term, NULL);
	close_sems(philo->data);
}

void	init_processes(t_data *data, t_philo *philos)
{
	int			i;
	pid_t		*pid;
	t_philo		*philo;

	pid = malloc(sizeof(pid_t) * (data->ph_num));
	i = -1;
	while (++i < data->ph_num)
	{
		philo = &philos[i];
		pid[i] = fork();
		if (pid[i] < 0)
			exit(0);
		if (!pid[i])
		{
			child_process(philo);
			free(philos);
			free(pid);
			exit(0);
		}
	}
	i = -1;
	while (++i < data->ph_num)
		sem_wait(philo->data->meals);
	free(pid);
}
