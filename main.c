/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:35 by artmende          #+#    #+#             */
/*   Updated: 2021/12/22 19:38:35 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>



t_philo	*init_philo_struct(t_misc *misc) // receive the number of philo
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

void	check_leaks(int sig)
{
	(void)sig;
	system("echo coucou");
//	system("leaks a.out");
	
	exit(1);
}

void	set_debug_signals(void)
{
	signal(SIGQUIT, check_leaks);
	signal(SIGINT, check_leaks);
}


int	main(int argc, char **argv)
{

	fd_debug = open("debug_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 00644);

//	set_debug_signals();

	pthread_t		*philo_thread;
	t_philo			*philo_struct;
	t_misc			misc;

	if (acquire_args(&misc, argc, argv) == 0)
		return (display_usage());


	philo_struct = init_philo_struct(&misc);
	if (!philo_struct)
		return (1); // in case malloc fail

	philo_thread = malloc(sizeof(pthread_t) * (misc.nbr_of_philo + 1));
	if (!philo_thread)
		return (1);

	create_threads(misc.nbr_of_philo, philo_thread, philo_struct);

/* 	int i = 0;
	while (i < misc.nbr_of_philo)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	} */

	pthread_join(philo_thread[misc.nbr_of_philo], NULL);

//	join_threads(misc.nbr_of_philo, );

//	terminate_philo(philo_struct, misc.nbr_of_philo);


	system("leaks a.out");

	return (0);
}
