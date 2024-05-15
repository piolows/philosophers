/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:49:14 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/04 15:55:02 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define BOLD    "\x1b[1m"
# define RESET   "\x1b[0m"

typedef struct s_data
{
	int				ph_num;
	int				end;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meals_req;
	size_t			timer;
	pthread_mutex_t	write;
	pthread_mutex_t	start_m;
	pthread_mutex_t	end_m;
	pthread_mutex_t	meals_m;
}	t_data;

typedef struct s_philo
{
	pthread_t		t;
	int				i;
	int				*end;
	int				meals;
	size_t			start;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				*rf;
	int				*lf;
	t_data			*data;
}	t_philo;

size_t		get_time(void);
int			ms_sleep(size_t milliseconds, t_philo *philo, int reset);
int			argcheck(int ac, char **av);
void		init_data(t_data *data, char **av);
long long	ph_atol(const char *str);
void		init_philos(t_data *data, t_philo *philo, pthread_mutex_t *forks,
				int *fork_flags);
int			init_mutexes(t_data *data, pthread_mutex_t *mutex);
void		init_threads(t_data *data, t_philo *philo);
void		init_flags(t_data *data, int *fork_flags);
void		destroy_mutexes(t_data *data, pthread_mutex_t *mutexes);
int			check_death(t_philo *philo);
int			take_r_fork(t_philo *philo);
int			take_l_fork(t_philo *philo);
int			take_forks(t_philo *philo);
void		*monitoring(void *p);
void		ph_print(t_philo *philo, int code);
int			ft_isdigit(int c);
size_t		ft_strlen(char *s);
int			drop_forks(t_philo *philo);
int			check_forks(t_philo *philo);
int			check_end(t_philo *philo);
int			check_lf(t_philo *philo);
int			check_rf(t_philo *philo);
int			check_forks(t_philo *philo);
int			check_meals(t_philo *philo);

#endif
