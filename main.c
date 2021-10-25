/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:08:35 by artmende          #+#    #+#             */
/*   Updated: 2021/10/25 17:36:37 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*my_tread_fct(void *arg)
{
	static int	i = 0;

	(*((int *)arg))++;

	i++;
	printf("Thread %d incremented i and its value is now %d\n", *((int *)arg), i);

	if (*((int *)arg) == 2)
	{
		printf("Thread %d is grounded. He has to wait 5 seconds !\n", *((int *)arg));
		sleep(5);
	}
	return (NULL);
}

int	main(void)
{
	int	count;
	pthread_t	thread1, thread2;

	count = 0;
	typedef	struct
	{
		int	*count_ptr;
		int	id;
	} to_thread;
	
	to_thread	t1 = {&count, 1};
	to_thread	t2 = {&count, 2};

	pthread_create(&thread1, NULL, &my_tread_fct, &t1);
	pthread_create(&thread2, NULL, &my_tread_fct, &t2);
	pthread_join(thread2, NULL);
	pthread_join(thread1, NULL);
	

	return (0);
}
