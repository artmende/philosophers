/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:47 by artmende          #+#    #+#             */
/*   Updated: 2021/12/16 20:00:34 by artmende         ###   ########.fr       */
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

#define SLEEPING_TIME 5000

typedef struct s_misc
{
	int		nbr_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nbr_of_cycles;
	int		start;
	long	ms_at_start;
}	t_misc;

typedef struct s_philo
{
	int				philo; // philo number
	pthread_mutex_t	*fork; // fork array
	t_misc			*misc;
}	t_philo;





void	*philo_s_way_of_life(void *arg);


/*	time_fct.c	*/
long	get_timestamp(long ms_start);
long	set_ms_start(void);

/*	from_libft	*/
int	ft_atoi(const char *str);

void	create_threads(int nbr_of_philo, pthread_t *philo_thread, t_philo *philo_struct);


#endif
