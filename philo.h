/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:47 by artmende          #+#    #+#             */
/*   Updated: 2021/12/28 15:28:16 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

#define SLEEPING_TIME 5

typedef struct s_misc
{
	int				nbr_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_of_cycles;
	int				start;
	long			ms_at_start;
	long			*last_eat_ms;
	pthread_mutex_t	speak;
}	t_misc;

typedef struct s_philo
{
	int				philo; // philo number
	int				finished;
	pthread_mutex_t	*fork; // fork array
	t_misc			*misc;
}	t_philo;





void	*philo_routine(void *arg);

void	*life_check(t_philo *philo_array);

void	set_forks(int *fork_a, int *fork_b, t_philo *philo);
void	philo_eat(t_philo *philo);


/*	time_fct.c	*/
long	get_timestamp(long ms_start);
long	set_ms_start(void);

/*	from_libft	*/
int	ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);

int	create_threads(pthread_t *philo_thread, t_philo *philo_struct);
void	join_threads(pthread_t *philo_thread, t_philo *philo_struct);

int	acquire_args(t_misc *misc, int argc, char **argv);
int	check_args_only_nbr(int argc, char **argv);
int	display_usage(char **argv);


void	ft_sleep_ms(long ms);

#endif
