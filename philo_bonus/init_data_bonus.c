/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:35:13 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/17 16:02:02 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	close_sems(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->end_s);
	sem_close(data->start_s);
	sem_close(data->write_s);
	sem_close(data->terminate);
	sem_close(data->meals);
	sem_close(data->meals_check);
}

void	destroy_sems(t_data *data)
{
	close_sems(data);
	sem_unlink("/forks");
	sem_unlink("/end_s");
	sem_unlink("/start_s");
	sem_unlink("/write_s");
	sem_unlink("/terminate");
	sem_unlink("/meals");
	sem_unlink("/meals_check");
}

void	init_sems(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/end_s");
	sem_unlink("/start_s");
	sem_unlink("/write_s");
	sem_unlink("/terminate");
	sem_unlink("/meals");
	sem_unlink("/meals_check");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->ph_num);
	data->end_s = sem_open("/end_s", O_CREAT | O_EXCL, 0644, 1);
	data->start_s = sem_open("/start_s", O_CREAT | O_EXCL, 0644, 1);
	data->write_s = sem_open("/write_s", O_CREAT | O_EXCL, 0644, 1);
	data->terminate = sem_open("/terminate", O_CREAT | O_EXCL, 0644, 0);
	data->meals = sem_open("/meals", O_CREAT | O_EXCL, 0644, 0);
	data->meals_check = sem_open("/meals_check", O_CREAT | O_EXCL, 0644, 1);
}

void	init_data(t_data *data, char **av)
{
	data->ph_num = ph_atol(av[1]);
	data->death_time = ph_atol(av[2]);
	data->eat_time = ph_atol(av[3]);
	data->sleep_time = ph_atol(av[4]);
	data->timer = get_time();
	if (av[5])
		data->meals_req = ph_atol(av[5]);
	else
		data->meals_req = -1;
}

void	init_philos(t_data *data, t_philo *philos)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->ph_num)
	{
		philo = &philos[i];
		philo->i = i + 1;
		philo->end = 0;
		philo->meals = 0;
		philo->start = get_time();
		philo->data = data;
	}
}
