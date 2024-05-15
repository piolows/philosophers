/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:35:13 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/01 17:33:56 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destory_fork_mutexes(pthread_mutex_t *mutexes, int c)
{
	int	i;

	i = -1;
	while (++i < c)
		pthread_mutex_destroy(&mutexes[i]);
}

void	destroy_mutexes(t_data *data, pthread_mutex_t *mutexes)
{
	destory_fork_mutexes(mutexes, data->ph_num);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->start_m);
	pthread_mutex_destroy(&data->end_m);
}

int	init_fork_mutexes(t_data *data, pthread_mutex_t *mutexes)
{
	int	i;

	i = -1;
	while (++i < data->ph_num)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			destory_fork_mutexes(mutexes, i);
			return (1);
		}
	}
	return (0);
}

int	init_mutexes(t_data *data, pthread_mutex_t *mutexes)
{
	if (init_fork_mutexes(data, mutexes))
		return (1);
	if (pthread_mutex_init(&data->write, NULL) != 0
		|| pthread_mutex_init(&data->start_m, NULL) != 0
		|| pthread_mutex_init(&data->end_m, NULL) != 0
		|| pthread_mutex_init(&data->meals_m, NULL) != 0)
	{
		destroy_mutexes(data, mutexes);
		return (1);
	}
	return (0);
}
