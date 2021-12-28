/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:47 by artmende          #+#    #+#             */
/*   Updated: 2021/12/28 18:05:32 by artmende         ###   ########.fr       */
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
	int				philo;
	int				finished;
	pthread_mutex_t	*fork;
	t_misc			*misc;
}	t_philo;

////////////////	main.c				////////////////
int		single_philo(t_misc *misc);
int		free_all(pthread_t *philo_thread, t_philo *philo_struct);
int		display_usage(char **argv);

////////////////	acquire_args.c		////////////////
int		acquire_args(t_misc *misc, int argc, char **argv);
int		check_args_only_nbr(int argc, char **argv);

////////////////	init_create_join.c	////////////////
t_philo	*init_philo_struct(t_misc *misc);
int		create_threads(pthread_t *philo_thread, t_philo *philo_struct);
void	join_threads(pthread_t *philo_thread, t_philo *philo_struct);

////////////////	life_check.c		////////////////
void	*life_check(t_philo *philo_array);
int		threads_not_finished(t_philo *philo_array);
int		meal_is_expired(t_philo *philo_array, int philo_id, long current_time);

////////////////	thread_routines.c	////////////////
void	*philo_routine(void *arg);
void	philo_loop_in_action(t_philo *philo, int times_eaten, long timestamp);
void	philo_eat(t_philo *philo);
void	set_forks(int *fork_a, int *fork_b, t_philo *philo);

////////////////	time_fct.c			////////////////
long	get_timestamp(long ms_start);
long	set_ms_start(void);
void	ft_sleep_ms(long ms);

////////////////	from_libft			////////////////
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);

#endif
