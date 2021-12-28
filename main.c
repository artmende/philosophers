/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:35 by artmende          #+#    #+#             */
/*   Updated: 2021/12/28 15:28:00 by artmende         ###   ########.fr       */
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

void	free_all(pthread_t *philo_thread, t_philo *philo_struct)
{
	int	i;

	i = 0;
	while (i < philo_struct->misc->nbr_of_philo)
	{
		pthread_mutex_destroy(&(philo_struct[i].fork)[i]);
		i++;
	}
	pthread_mutex_destroy(&philo_struct->misc->speak);
	free(philo_struct->fork);
	free(philo_struct->misc->last_eat_ms);
	free(philo_struct);
}

int	single_philo(t_misc *misc)
{
	printf("0 0 has taken a fork\n");
	misc->ms_at_start = set_ms_start();
	ft_sleep_ms(misc->time_to_die);
	// maybe just usleep ? 
	printf("%ld 0 died\n", misc->time_to_die + 1);
	return (0);
}



int	main(int argc, char **argv)
{
	pthread_t		*philo_thread;
	t_philo			*philo_struct;
	t_misc			misc;

	if (acquire_args(&misc, argc, argv) == 0)
		return (display_usage(argv));
	if (misc.nbr_of_philo == 1)
		return (single_philo(&misc));
	philo_struct = init_philo_struct(&misc);
	if (!philo_struct)
		return (1); // in case malloc fail

	philo_thread = malloc(sizeof(pthread_t) * misc.nbr_of_philo);
	if (!philo_thread)
		return (1);
	if (!create_threads(philo_thread, philo_struct))
		return (1);
	life_check(philo_struct);
	join_threads(philo_thread, philo_struct);
	free_all(philo_thread, philo_struct);



/* 

malloced stuff : 

threads
forks
last eat array
philo struct
need to destroy mutex first% 

 */



//	usleep(5000); // leave the time to the threads to finish.
	// let's replace that with pthread_join, and free all 
	// need to have special fct for the case where a philo is alone




/* 	char	leaks_str[5 + strlen(argv[0])];
	memset(leaks_str, 0, (5 + strlen(argv[0])) * sizeof(char));
	strcat(leaks_str, "leaks ");
	char	*temp = strdup(argv[0]);
	strcat(leaks_str, &temp[2]);
	free(temp);

	system(leaks_str);
 */


	return (0);
}
