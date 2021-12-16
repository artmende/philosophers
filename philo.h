/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:47 by artmende          #+#    #+#             */
/*   Updated: 2021/12/16 18:50:12 by artmende         ###   ########.fr       */
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

typedef struct s_philo
{
	int				philo; // philo number
	pthread_mutex_t	*fork; // fork array
	int				*start;
	int				*ms_at_start;
}	t_philo;

void	*philo_s_way_of_life(void *arg);


/*	from_libft	*/
int	ft_atoi(const char *str);

void	create_threads(int nbr_of_philo, pthread_t *philo_thread, t_philo *philo_struct);


#endif
