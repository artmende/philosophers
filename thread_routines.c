/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:13:34 by artmende          #+#    #+#             */
/*   Updated: 2021/12/28 19:05:34 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->misc->start == 0)
		usleep(50);
	if (philo->philo % 2)
	{
		if (philo->misc->time_to_eat > 5)
			ft_sleep_ms(philo->misc->time_to_eat * 2 / 3);
		else
			ft_sleep_ms(5);
	}
	philo_loop_in_action(philo, 0, 0);
	return (NULL);
}

void	philo_loop_in_action(t_philo *philo, int times_eaten, long timestamp)
{
	while (philo->misc->start)
	{
		philo_eat(philo);
		times_eaten++;
		if (times_eaten == philo->misc->nbr_of_cycles)
			philo->finished = 1;
		timestamp = get_timestamp(philo->misc->ms_at_start);
		pthread_mutex_lock(&philo->misc->speak);
		if (philo->misc->start)
			printf("%ld %d is sleeping\n", timestamp, philo->philo);
		pthread_mutex_unlock(&philo->misc->speak);
		ft_sleep_ms(philo->misc->time_to_sleep);
		timestamp = get_timestamp(philo->misc->ms_at_start);
		pthread_mutex_lock(&philo->misc->speak);
		if (philo->misc->start)
			printf("%ld %d is thinking\n", timestamp, philo->philo);
		pthread_mutex_unlock(&philo->misc->speak);
	}
}

void	philo_eat(t_philo *philo)
{
	long	timestamp;
	int		fork_a;
	int		fork_b;

	set_forks(&fork_a, &fork_b, philo);
	pthread_mutex_lock(&philo->fork[fork_a]);
	timestamp = get_timestamp(philo->misc->ms_at_start);
	pthread_mutex_lock(&philo->misc->speak);
	if (philo->misc->start)
		printf("%ld %d has taken a fork\n", timestamp, philo->philo);
	pthread_mutex_unlock(&philo->misc->speak);
	pthread_mutex_lock(&philo->fork[fork_b]);
	timestamp = get_timestamp(philo->misc->ms_at_start);
	philo->misc->last_eat_ms[philo->philo] = timestamp;
	pthread_mutex_lock(&philo->misc->speak);
	if (philo->misc->start)
	{
		printf("%ld %d has taken a fork\n", timestamp, philo->philo);
		printf("%ld %d is eating\n", timestamp, philo->philo);
	}
	pthread_mutex_unlock(&philo->misc->speak);
	ft_sleep_ms(philo->misc->time_to_eat);
	pthread_mutex_unlock(&philo->fork[fork_a]);
	pthread_mutex_unlock(&philo->fork[fork_b]);
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
