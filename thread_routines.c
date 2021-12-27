/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:13:34 by artmende          #+#    #+#             */
/*   Updated: 2021/12/27 18:07:04 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_not_finished(t_philo *philo_array)
{
	int	i;

	i = 0;
	while (i < philo_array->misc->nbr_of_philo)
	{
		if (philo_array[i].finished == 0)
			return (1);
		i++;
	}
	return (0);
}

void	*life_check(t_philo *philo_array)
{
	int		i;
	long	current_time;

	while (philo_array->misc->start == 0)
	{}
	while (threads_not_finished(philo_array))
	{
		i = 0;
		current_time = get_timestamp(philo_array->misc->ms_at_start);
		while (i < philo_array[0].misc->nbr_of_philo)
		{
			if (current_time - philo_array->misc->last_eat_ms[i] > philo_array->misc->time_to_die)
			{
				philo_array->misc->start = 0; // it is now forbidden to speak
				pthread_mutex_lock(&philo_array->misc->speak);
				printf("%ld %d died\n", current_time, i);
				ft_sleep_ms(500);
				pthread_mutex_unlock(&philo_array->misc->speak);
				return (0);
			}
			i++;
		}
	}
	// maybe here take the right to speak, put start to 0 and wait, before unlocking
	philo_array->misc->start = 0;
	ft_sleep_ms(500);
//	printf("All philos succesfully completed their %d meals !\n", philo_array->misc->nbr_of_cycles);
	return (0);
}

void	philo_loop_in_action(t_philo *philo, int times_eaten, long timestamp)
{
	while (philo->misc->start)
	{
		philo_eat(philo);
		times_eaten++;
		if (times_eaten == philo->misc->nbr_of_cycles)
			philo->finished = 1;
		if (philo->misc->start == 0)
			break ;
		timestamp = get_timestamp(philo->misc->ms_at_start);
		pthread_mutex_lock(&philo->misc->speak);
		if (philo->misc->start == 0)
			printf("got it 3\n"); ////////////////
		printf("%ld %d is sleeping\n", timestamp, philo->philo);
		pthread_mutex_unlock(&philo->misc->speak);
		ft_sleep_ms(philo->misc->time_to_sleep);
		if (philo->misc->start == 0)
			break ;
		timestamp = get_timestamp(philo->misc->ms_at_start);
		pthread_mutex_lock(&philo->misc->speak);
		if (philo->misc->start == 0)
			printf("got it 4\n"); ////////////////
		printf("%ld %d is thinking\n", timestamp, philo->philo);
		pthread_mutex_unlock(&philo->misc->speak);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo; // use pointer instead
	int		i;
	long	timestamp;

	philo = (t_philo *)arg; // can initialize i at this line
	i = 0;
	while (philo->misc->start == 0)
		usleep(50);
	if (philo->philo % 2)
		ft_sleep_ms(philo->misc->time_to_eat * 2 / 3);

	philo_loop_in_action(philo, 0, 0);

/* 	while (1)
	{
		if (philo->misc->start == 0)
			break ;
		philo_eat(philo);
		i++;
		if (i == philo->misc->nbr_of_cycles)
			philo->finished = 1;
		if (philo->misc->start == 0)
			break ;
		timestamp = get_timestamp(philo->misc->ms_at_start);
		pthread_mutex_lock(&philo->misc->speak);
		printf("%ld %d is sleeping\n", timestamp, philo->philo);
		pthread_mutex_unlock(&philo->misc->speak);
		ft_sleep_ms(philo->misc->time_to_sleep);
		if (philo->misc->start == 0)
			break ;
		timestamp = get_timestamp(philo->misc->ms_at_start);
		pthread_mutex_lock(&philo->misc->speak);
		printf("%ld %d is thinking\n", timestamp, philo->philo);
		pthread_mutex_unlock(&philo->misc->speak);
	} */
	return (NULL);
}

void	set_forks(int *fork_a, int *fork_b, t_philo *philo)
{
	if (philo->philo == philo->misc->nbr_of_philo - 1)
	{
		*fork_a = philo->philo;
		*fork_b = 0;
	}
	else
	{
		*fork_a = philo->philo;
		*fork_b = *fork_a + 1;
	}
}

void	unlock_mutex(pthread_mutex_t *a, pthread_mutex_t *b)
{
	if (a)
		pthread_mutex_unlock(a);
	if (b)
		pthread_mutex_unlock(b);
}

void	philo_eat(t_philo *philo)
{
	long	timestamp;
	int		fork_a;
	int		fork_b;

	set_forks(&fork_a, &fork_b, philo);
	pthread_mutex_lock(&philo->fork[fork_a]);
	if (philo->misc->start == 0)
		return (unlock_mutex(&philo->fork[fork_a], NULL));
	timestamp = get_timestamp(philo->misc->ms_at_start);
	pthread_mutex_lock(&philo->misc->speak);
	if (philo->misc->start == 0)
		printf("got it 1\n"); ////////////////
	printf("%ld %d has taken a fork\n", timestamp, philo->philo);
	pthread_mutex_unlock(&philo->misc->speak);
	pthread_mutex_lock(&philo->fork[fork_b]);
	if (philo->misc->start == 0)
		return (unlock_mutex(&philo->fork[fork_a], &philo->fork[fork_b]));
	timestamp = get_timestamp(philo->misc->ms_at_start);
	philo->misc->last_eat_ms[philo->philo] = timestamp;
	pthread_mutex_lock(&philo->misc->speak);
	if (philo->misc->start == 0)
		printf("got it 2\n"); ////////////////
	printf("%ld %d has taken a fork\n", timestamp, philo->philo);
	printf("%ld %d is eating\n", timestamp, philo->philo);
	pthread_mutex_unlock(&philo->misc->speak);
	ft_sleep_ms(philo->misc->time_to_eat);
	unlock_mutex(&philo->fork[fork_a], &philo->fork[fork_b]);
}
