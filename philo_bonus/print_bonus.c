/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:30:28 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/17 16:00:53 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ph_print(t_philo *philo, int code)
{
	if (!check_end(philo))
	{
		sem_wait(philo->data->write_s);
		printf(RESET "%ld\t", get_time() - philo->data->timer);
		if (code == 1)
			printf(GREEN BOLD "%d is eating\n" RESET, philo->i);
		if (code == 2)
			printf(YELLOW "%d has taken a fork\n" RESET, philo->i);
		if (code == 3)
			printf(BLUE "%d is sleeping\n" RESET, philo->i);
		if (code == 4)
			printf(MAGENTA "%d is thinking\n" RESET, philo->i);
		sem_post(philo->data->write_s);
	}
}
