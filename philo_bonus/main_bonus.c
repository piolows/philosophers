/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:14:26 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/04 16:52:01 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	data;

	if (argcheck(ac, av))
		return (0);
	philos = malloc(sizeof(struct s_philo) * ph_atol(av[1]));
	if (!philos)
		return (0);
	init_data(&data, av);
	init_sems(&data);
	init_philos(&data, philos);
	init_processes(&data, philos);
	destroy_sems(&data);
	free(philos);
	return (0);
}
