/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:35:13 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/04 15:27:13 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data, char **av)
{
	data->ph_num = ph_atol(av[1]);
	data->end = 0;
	data->death_time = ph_atol(av[2]);
	data->eat_time = ph_atol(av[3]);
	data->sleep_time = ph_atol(av[4]);
	data->timer = get_time();
	if (av[5])
		data->meals_req = ph_atol(av[5]);
	else
		data->meals_req = -1;
}

void	init_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks,
			int *fork_flags)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->ph_num)
	{
		philo = &philos[i];
		philo->i = i + 1;
		philo->end = &data->end;
		philo->meals = 0;
		philo->start = get_time();
		if (i == 0)
			philo->l_fork = &forks[data->ph_num - 1];
		else
			philo->l_fork = &forks[i - 1];
		philo->r_fork = &forks[i];
		if (i == 0)
			philo->lf = &fork_flags[data->ph_num - 1];
		else
			philo->lf = &fork_flags[i - 1];
		philo->rf = &fork_flags[i];
		philo->data = data;
	}
}

void	init_flags(t_data *data, int *fork_flags)
{
	int	i;

	i = -1;
	while (++i < data->ph_num)
		fork_flags[i] = 0;
}
