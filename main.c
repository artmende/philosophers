/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:35 by artmende          #+#    #+#             */
/*   Updated: 2021/12/23 17:03:03 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>



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
	pthread_mutex_init(&misc->speak, NULL);
	i = 0;
	while (i < misc->nbr_of_philo)
	{
		ret[i].philo = i;
		ret[i].finished = 0;
		ret[i].fork = fork;
		ret[i].misc = misc;
		pthread_mutex_init(&(ret[i].fork)[i], NULL);
		i++;
	}
	return (ret);
}

void	terminate_philo(t_philo *philo_struct, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		pthread_mutex_destroy(&(philo_struct[i].fork)[i]);
		i++;
	}
	free(philo_struct[0].fork);
	free(philo_struct);
}





int	main(int argc, char **argv)
{
	pthread_t		*philo_thread;
	t_philo			*philo_struct;
	t_misc			misc;

	if (acquire_args(&misc, argc, argv) == 0)
		return (display_usage(argv));
	philo_struct = init_philo_struct(&misc);
	if (!philo_struct)
		return (1); // in case malloc fail

	philo_thread = malloc(sizeof(pthread_t) * misc.nbr_of_philo);
	if (!philo_thread)
		return (1);
	create_threads(misc.nbr_of_philo, philo_thread, philo_struct);
	life_check(philo_struct);


//	system("leaks a.out");

	return (0);
}
