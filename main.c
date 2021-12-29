/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:35 by artmende          #+#    #+#             */
/*   Updated: 2021/12/29 14:52:17 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (1);
	philo_thread = malloc(sizeof(pthread_t) * misc.nbr_of_philo);
	if (!philo_thread)
		return (1);
	if (!create_threads(philo_thread, philo_struct))
		return (free_all(philo_thread, philo_struct));
	misc.ms_at_start = set_ms_start();
	misc.start = 1;
	life_check(philo_struct);
	join_threads(philo_thread, philo_struct);
	free_all(philo_thread, philo_struct);
	return (0);
}

int	single_philo(t_misc *misc)
{
	printf("0 0 has taken a fork\n");
	misc->ms_at_start = set_ms_start();
	ft_sleep_ms(misc->time_to_die);
	printf("%ld 0 died\n", misc->time_to_die + 1);
	return (0);
}

int	free_all(pthread_t *philo_thread, t_philo *philo_struct)
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
	free(philo_thread);
	return (1);
}

int	display_usage(char **argv)
{
	printf("\nUsage : %s [number_of_philosophers] [time_to_die] ", argv[0]);
	printf("[time_to_eat] [time_to_sleep] [number_of_cycles]\n");
	printf("\n[number_of_cycles] is optional.\n");
	printf("All times are expressed in ms.\n");
	printf("\nFor an even number of philo : [time_to_die] needs to be at ");
	printf("least 2 times [time_to_eat] in order for the philos to not die.\n");
	printf("For an odd number of philo it's 3 times.\n");
	printf("If [time_to_eat] + [time_to_sleep] exceeds [time_to_die], the ");
	printf("philos will die too.\n");
	printf("\nEnjoy this little simulation ! The results can be visualized ");
	printf("here : https://nafuka11.github.io/philosophers-visualizer\n");
	printf("Thank you Naho Fukada for the vizualizer ! ");
	printf("--> https://github.com/nafuka11\n");
	return (1);
}
