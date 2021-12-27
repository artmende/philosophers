/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_create_join.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:20:34 by artmende          #+#    #+#             */
/*   Updated: 2021/12/27 16:20:39 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(int nbr_of_philo, pthread_t *philo_thread, t_philo *philo_struct)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_create(&philo_thread[i], NULL, philo_routine, &philo_struct[i]);
		i++;
	}
	usleep(100);
	philo_struct[0].misc->ms_at_start = set_ms_start();
	philo_struct[0].misc->start = 1;
	
}
