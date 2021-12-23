/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:13:34 by artmende          #+#    #+#             */
/*   Updated: 2021/12/23 14:05:24 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_not_finished(t_philo *philo_array)
{
	int	i;

	i = 0;
	while (i < philo_array[0].misc->nbr_of_philo)
	{
		if (philo_array[i].finished == 0)
		{
/* 			if (get_timestamp(philo_array->misc->ms_at_start) > 1002)
			{
				printf("return 1 because of %d\n", i);
			} */
			return (1);
		}
		i++;
	}
	return (0);
}

void	*life_thread(void *arg)
{
	t_philo	*philo_array;
//	t_misc	*misc;
	int		i;
	long	current_time;

	philo_array = (t_philo *)arg;
	while (philo_array[0].misc->start == 0)
	{}
	while (threads_not_finished(philo_array)) // need to find a way to detect when they all finished
	{
		i = 0;
		current_time = get_timestamp(philo_array[0].misc->ms_at_start);
//		dprintf(fd_debug, "timestamp : %ld\n", current_time);
		while (i < philo_array[0].misc->nbr_of_philo)
		{
			if (current_time - philo_array[0].misc->last_eat_ms[i] > philo_array[0].misc->time_to_die)
			{
				philo_array[0].misc->start = 0; // it is now forbidden to speak
				printf("%ld %d died\n", current_time, i);
				return (0);
			}
			i++;
		}
	}
//	printf("coucou %ld", get_timestamp(philo_array->misc->ms_at_start));
	return (0);
}

void	*philo_s_way_of_life(void *arg)
{
	t_philo	*philo; // use pointer instead
	int		i;
	long	timestamp;

	philo = (t_philo *)arg; // can initialize i at this line
	i = 0;
	while (philo->misc->start == 0)
	{}
	if (philo->philo % 2 /* && printf("philo %d is waiting\n", philo->philo) */)
		ft_sleep_ms(5);
	while (1)
	{
		ft_sleep_ms(1);
		if (philo->misc->start == 0)
			break ;
		philo_eat(philo);
		i++;
		if (i == philo->misc->nbr_of_cycles)
			philo->finished = 1;
		if (philo->misc->start == 0)
			break ;
		timestamp = get_timestamp(philo->misc->ms_at_start);
		printf("%ld %d is sleeping\n", timestamp, philo->philo);
		ft_sleep_ms(philo->misc->time_to_sleep);
		if (philo->misc->start == 0)
			break ;
		timestamp = get_timestamp(philo->misc->ms_at_start);
		printf("%ld %d is thinking\n", timestamp, philo->philo);
//		i++;
//		if (i == philo->misc->nbr_of_cycles)
//			(philo->finished = 1) && printf("%d has finished\n", philo->philo); // to indicate that it has finished

/* 		printf("cycle %d\n", i);
		if (philo->misc->start == 0)
			break ;
		printf("%ld - philo %d has started eating.\n", get_timestamp(philo->misc->ms_at_start), philo->philo);
		ft_sleep_ms(philo->misc->time_to_eat);
		if (philo->misc->start == 0)
			break ;
		printf("%ld - philo %d has started sleeping.\n", get_timestamp(philo->misc->ms_at_start), philo->philo);
		ft_sleep_ms(philo->misc->time_to_sleep);
		if (philo->misc->start == 0)
			break ;
		printf("%ld - philo %d has started thinking.\n", get_timestamp(philo->misc->ms_at_start), philo->philo);
		i++;
		 */
	}



	// need to receive its nbr
	// need to receive array of fork
	return (NULL);
}

void	set_forks(int *fork_a, int *fork_b, t_philo *philo)
{
	if (philo->philo == philo->misc->nbr_of_philo - 1)
	{
//		*fork_a = 0;
//		*fork_b = philo->philo;
		*fork_a = philo->philo;
		*fork_b = 0;

	}
	else
	{
		*fork_a = philo->philo;
		*fork_b = *fork_a + 1;
	}
}

void	philo_eat(t_philo *philo)
{
	long	timestamp;
	int		fork_a;
	int		fork_b;

	set_forks(&fork_a, &fork_b, philo);
	pthread_mutex_lock(&philo->fork[fork_a]);
	if (philo->misc->start == 0)
		return ;
	timestamp = get_timestamp(philo->misc->ms_at_start);
	printf("%ld %d has taken a fork\n", timestamp, philo->philo);
	pthread_mutex_lock(&philo->fork[fork_b]);
	if (philo->misc->start == 0)
		return ;
	timestamp = get_timestamp(philo->misc->ms_at_start);
	philo->misc->last_eat_ms[philo->philo] = timestamp;
	printf("%ld %d has taken a fork\n", timestamp, philo->philo);
	printf("%ld %d is eating\n", timestamp, philo->philo);
	ft_sleep_ms(philo->misc->time_to_eat);
	pthread_mutex_unlock(&philo->fork[fork_a]);
	pthread_mutex_unlock(&philo->fork[fork_b]);
	// need to lock both forks
	// need to declare eating
	// need to release forks

	

}
