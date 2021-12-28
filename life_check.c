/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:44:41 by artmende          #+#    #+#             */
/*   Updated: 2021/12/28 18:19:24 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_check(t_philo *philo_array)
{
	int		i;
	long	current_time;

	while (threads_not_finished(philo_array))
	{
		i = 0;
		current_time = get_timestamp(philo_array->misc->ms_at_start);
		while (i < philo_array->misc->nbr_of_philo)
		{
			if (meal_is_expired(philo_array, i, current_time))
			{
				philo_array->misc->start = 0;
				pthread_mutex_lock(&philo_array->misc->speak);
				printf("%ld %d died\n", current_time, i);
				ft_sleep_ms(500);
				pthread_mutex_unlock(&philo_array->misc->speak);
				return (0);
			}
			i++;
		}
	}
	philo_array->misc->start = 0;
	return (0);
}

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

int	meal_is_expired(t_philo *philo_array, int philo_id, long current_time)
{
	return (current_time - philo_array->misc->last_eat_ms[philo_id]
		> philo_array->misc->time_to_die);
}
