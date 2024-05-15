/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:15:05 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/04 20:03:45 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	checkfornum(char *s)
{
	int	i;
	int	n;

	i = -1;
	n = 1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			n = 0;
	return (n);
}

long long	ph_atol(const char *str)
{
	int			i;
	long long	sign;
	long long	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((result == 922337203685477580
				&& str[i] > '7') || (result > 922337203685477580))
			return (-1 * (sign != -1));
		result = (result * 10) + (str[i++] - '0');
	}
	return (result * sign);
}

int	err_msg(void)
{
	printf(RED BOLD "\nInvalid arguments.\n" RESET BOLD);
	printf("%s %s",
		"./philo_bonus number_of_philos",
		"time_to_die time_to_eat time_to_sleep ");
	printf(YELLOW BOLD "meals_required\n" RESET);
	printf(RED "Inputs must all be positive integers.\n" RESET);
	printf(RED "At least 1 philosopher must be present.\n" RESET);
	printf(YELLOW BOLD "Meals_required is optional. " RESET);
	printf(YELLOW "If included, it must be greater than 0.\n\n" RESET);
	return (1);
}

int	argcheck(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (err_msg());
	while (++i < ac)
	{
		if (!checkfornum(av[i]))
			return (err_msg());
	}
	if (ft_strlen(av[1]) > 10 || ft_strlen(av[2]) > 10 || ft_strlen(av[3]) > 10
		|| ft_strlen(av[4]) > 10 || (av[5] && ft_strlen(av[5]) > 10)
		|| ph_atol(av[1]) > 2147483647 || ph_atol(av[2]) > 2147483647
		|| ph_atol(av[3]) > 2147483647 || ph_atol(av[4]) > 2147483647
		|| (av[5] && ph_atol(av[5]) > 2147483647) || ph_atol(av[1]) <= 0
		|| (av[5] && ph_atol(av[5]) <= 0))
		return (err_msg());
	return (0);
}
