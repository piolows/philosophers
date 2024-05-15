/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:30:28 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/04 20:10:44 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_print(t_philo *philo, int code)
{
	if (!check_end(philo))
	{
		pthread_mutex_lock(&philo->data->write);
		printf(RESET "%ld\t", get_time() - philo->data->timer);
		if (code == 1)
			printf(GREEN BOLD "%d is eating\n" RESET, philo->i);
		if (code == 2)
			printf(YELLOW "%d has taken a fork\n" RESET, philo->i);
		if (code == 3)
			printf(BLUE "%d is sleeping\n" RESET, philo->i);
		if (code == 4)
			printf(MAGENTA "%d is thinking\n" RESET, philo->i);
		pthread_mutex_unlock(&philo->data->write);
	}
}
