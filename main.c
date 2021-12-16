/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:35 by artmende          #+#    #+#             */
/*   Updated: 2021/12/16 18:51:12 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_s_way_of_life(void *arg)
{
	t_philo	philo;

	philo = (*(t_philo *)arg);
	while (*(philo.start) == 0)
	{}
	// grabbing the forks
	// usleep for the time needed to eat
	// releasing the forks
	// usleep for the time needed to sleep
	// back to grabbing the fork, but before "started thinking"
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

t_philo	*init_philo_struct(int	nbr, int *start) // receive the number of philo
{
	int				i;
	t_philo			*ret;
	pthread_mutex_t	*fork;

	ret = malloc(sizeof(t_philo) * nbr);
//	if (!ret)
//		return (NULL);
	fork = malloc(sizeof(pthread_mutex_t) * nbr);
	if (!ret || !fork)
		return (NULL);
	*start = 0;
	i = 0;
	while (i < nbr)
	{ // need to give them ptr to ms_at_start
		ret[i].start = start;
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
	int				nbr_of_philo;
	int				start;

	if (argc < 2 || argc > 5)
		return (1);

	nbr_of_philo = ft_atoi(argv[1]);

	philo_struct = init_philo_struct(nbr_of_philo, &start);
	if (!philo_struct)
		return (1); // in case malloc fail

	philo_thread = malloc(sizeof(pthread_t) * nbr_of_philo);
	if (!philo_thread)
		return (1);

	int	i = 0;

	create_threads(nbr_of_philo, philo_thread, philo_struct);

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
