/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_create_join.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:20:34 by artmende          #+#    #+#             */
/*   Updated: 2021/12/28 15:37:25 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(pthread_t *philo_thread, t_philo *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo_struct->misc->nbr_of_philo)
	{
//		printf("coucou\n");
		if (pthread_create(&philo_thread[i], NULL, philo_routine, &philo_struct[i]))
		{
			printf("Error while creating the threads !\n");
			pthread_mutex_lock(&philo_struct->misc->speak);
			philo_struct->misc->start = 1;
			usleep(100);
			philo_struct->misc->start = 0;
			usleep(500);
			return (0);
		}
		i++;
	} // check that no error
//	return (1);

	// put those following lines in the main

	usleep(100);
	philo_struct->misc->ms_at_start = set_ms_start();
	philo_struct->misc->start = 1;
	return (1);
}

void	join_threads(pthread_t *philo_thread, t_philo *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo_struct->misc->nbr_of_philo)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	}
}
