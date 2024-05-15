/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:10:16 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/14 16:37:35 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

size_t	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		write(2, "Could not get time of day.\n", 27);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ms_sleep(size_t milliseconds, t_philo *philo, int reset)
{
	size_t	start;

	if (reset == 1)
	{
		sem_wait(philo->data->start_s);
		philo->start = get_time();
		sem_post(philo->data->start_s);
	}
	start = get_time();
	while ((get_time() - start) < milliseconds && !check_death(philo))
		usleep(200);
	return (0);
}
