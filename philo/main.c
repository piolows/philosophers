/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:32 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/04 15:54:54 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_all(t_philo *philos, pthread_mutex_t *forks, int *fork_flags)
{
	if (philos)
		free(philos);
	if (forks)
		free(forks);
	if (fork_flags)
		free(fork_flags);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				*fork_flags;

	if (argcheck(ac, av))
		return (0);
	philos = malloc(sizeof(struct s_philo) * ph_atol(av[1]));
	forks = malloc(sizeof(pthread_mutex_t) * ph_atol(av[1]));
	fork_flags = malloc(sizeof(int) * ph_atol(av[1]));
	if (!philos || !forks || !fork_flags)
		return (free_all(philos, forks, fork_flags));
	init_data(&data, av);
	init_flags(&data, fork_flags);
	if (init_mutexes(&data, forks))
		return (free_all(philos, forks, fork_flags));
	init_philos(&data, philos, forks, fork_flags);
	init_threads(&data, philos);
	destroy_mutexes(&data, forks);
	return (free_all(philos, forks, fork_flags));
}
