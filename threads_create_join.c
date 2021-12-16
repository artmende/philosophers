/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_create_join.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:20:34 by artmende          #+#    #+#             */
/*   Updated: 2021/12/16 19:11:34 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(int nbr_of_philo, pthread_t *philo_thread, t_philo *philo_struct)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_create(&philo_thread[i], NULL, philo_s_way_of_life, &philo_struct[i]);
		i++;
	}
	set_ms_start(); // write initial ms value
	*(philo_struct[0].start) = 1;
}
