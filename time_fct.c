/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 19:08:32 by artmende          #+#    #+#             */
/*   Updated: 2021/12/17 14:15:34 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(long ms_start)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (((long)(tp.tv_usec / 1000) + tp.tv_sec * 1000) - ms_start);
}

long	set_ms_start(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((long)(tp.tv_usec / 1000) + tp.tv_sec * 1000);
}

void	ft_sleep_ms(long ms)
{
	long	start_time;

	start_time = set_ms_start();
	while (get_timestamp(start_time) < ms)
	{
		usleep(ms * 2);
	}
}
