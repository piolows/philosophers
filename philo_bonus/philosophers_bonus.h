/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:49:14 by ppolinta          #+#    #+#             */
/*   Updated: 2024/04/17 16:21:15 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

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
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meals_req;
	size_t			timer;
	sem_t			*forks;
	sem_t			*write_s;
	sem_t			*end_s;
	sem_t			*start_s;
	sem_t			*terminate;
	sem_t			*meals;
	sem_t			*meals_check;
}	t_data;

typedef struct s_philo
{
	pthread_t		mon;
	pthread_t		term;
	int				i;
	int				end;
	int				meals;
	size_t			start;
	t_data			*data;
}	t_philo;

int			argcheck(int ac, char **av);
size_t		ft_strlen(char *s);
int			ft_isdigit(int c);
long long	ph_atol(const char *str);
int			ms_sleep(size_t milliseconds, t_philo *philo, int reset);
size_t		get_time(void);
void		thinking(t_philo *philo);
void		init_data(t_data *data, char **av);
void		init_philos(t_data *data, t_philo *philos);
void		init_sems(t_data *data);
void		init_processes(t_data *data, t_philo *philos);
void		destroy_sems(t_data *data);
void		close_sems(t_data *data);
void		ph_print(t_philo *philo, int code);
int			check_death(t_philo *philo);
int			check_end(t_philo *philo);
void		*checkterm(void *p);
void		*monitor(void *p);
int			check_meals(t_philo *philo);

#endif
