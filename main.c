/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:35 by artmende          #+#    #+#             */
/*   Updated: 2021/12/13 17:34:49 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*my_tread_fct(void *arg)
{
	static int	i = 0;

	int	id = 

	i++;
	*((int *)arg) = *((int *)arg) + 1;
	printf("Thread %d incremented i and its value is now %d\n", *((int *)arg), i);

	if (*((int *)arg) == 2)
	{
		printf("Thread %d is grounded. He has to wait 5 seconds !\n", *((int *)arg));
		sleep(5);
	}
	return (NULL);
}

void	*philo_s_way_of_life(void *arg)
{
	t_philo	philo;

	philo = (*(t_philo *)arg);
	int	i = 0;
	while (i < 10)
	{
		printf("philo %d has started eating.\n", philo.philo);
		usleep(5000);
		printf("philo %d has started sleeping.\n", philo.philo);
		usleep(5000);
		printf("philo %d has started thinking.\n", philo.philo);
		i++;
	}



	// need to receive its nbr
	// need to receive array of fork
	return (NULL);
}

t_philo	*init_philo_struct(int	nbr) // receive the number of philo
{
	int				i;
	t_philo			*ret;
	pthread_mutex_t	*fork;

	ret = malloc(sizeof(t_philo) * nbr);
	if (!ret)
		return (NULL);
	fork = malloc(sizeof(pthread_mutex_t) * nbr);
	i = 0;
	while (i < nbr)
	{
		ret[i].philo = i;
		ret[i].fork = fork;
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
	int	nbr_of_philo;

	if (argc < 2 || argc > 5) // not 5
		return (1);

	nbr_of_philo = atoi(argv[1]);

	philo_struct = init_philo_struct(nbr_of_philo);

	philo_thread = malloc(sizeof(pthread_t) * nbr_of_philo);

	int	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_create(&philo_thread[i], NULL, philo_s_way_of_life, &philo_struct[i]);
		i++;
	}
	i = 0;
	while (i < nbr_of_philo)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	}

	terminate_philo(philo_struct, nbr_of_philo);


	system("leaks a.out");

	return (0);
}