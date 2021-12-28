/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_create_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:20:34 by artmende          #+#    #+#             */
/*   Updated: 2021/12/28 19:10:51 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo_struct(t_misc *misc)
{
	int				i;
	t_philo			*ret;
	pthread_mutex_t	*fork;

	ret = malloc(sizeof(t_philo) * misc->nbr_of_philo);
	fork = malloc(sizeof(pthread_mutex_t) * misc->nbr_of_philo);
	misc->last_eat_ms = malloc(sizeof(long) * misc->nbr_of_philo);
	if (!ret || !fork || !misc->last_eat_ms)
		return (NULL);
	memset(misc->last_eat_ms, 0, sizeof(long) * misc->nbr_of_philo);
	misc->start = 0;
	if (pthread_mutex_init(&misc->speak, NULL))
		return (NULL);
	i = 0;
	while (i < misc->nbr_of_philo)
	{
		ret[i].philo = i;
		ret[i].finished = 0;
		ret[i].fork = fork;
		ret[i].misc = misc;
		if (pthread_mutex_init(&(ret[i].fork)[i], NULL))
			return (NULL);
		i++;
	}
	return (ret);
}

int	create_threads(pthread_t *philo_thread, t_philo *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo_struct->misc->nbr_of_philo)
	{
		if (pthread_create(&philo_thread[i], NULL, philo_routine,
				&philo_struct[i]))
		{
			printf("Error while creating the threads !\n");
			pthread_mutex_lock(&philo_struct->misc->speak);
			philo_struct->misc->start = 1;
			usleep(500);
			philo_struct->misc->start = 0;
			usleep(500);
			return (0);
		}
		i++;
	}
	return (1);
}

void	join_threads(pthread_t *philo_thread, t_philo *philo_struct)
{
	int	i;

	i = 0;
	while (philo_thread && i < philo_struct->misc->nbr_of_philo)
	{
//		pthread_join(philo_thread[i], NULL);
		i++;
	}
	usleep(5000);
}
