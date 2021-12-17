/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:59:32 by artmende          #+#    #+#             */
/*   Updated: 2021/12/17 16:21:40 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	acquire_args(t_misc *misc, int argc, char **argv)
{
	if (argc > 6 || argc < 5 || check_args_only_nbr(argc, argv) == 0)
		return (0);
	misc->nbr_of_philo = ft_atoi(argv[1]);
	if (misc->nbr_of_philo == 0)
	{
		printf("There are no philosophers.\n");
		return (0);
	}
	misc->time_to_die = ft_atoi(argv[2]);
	misc->time_to_eat = ft_atoi(argv[3]);
	misc->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		misc->nbr_of_cycles = ft_atoi(argv[5]);
	else
		misc->nbr_of_cycles = -1;
	return (1);
}

int	check_args_only_nbr(int argc, char **argv)
{
	int		i;
	char	*str;

	i = 0;
	while (i < argc)
	{
		str = argv[i + 1];
		while (str && *str)
		{
			if (ft_strchr("0123456789", *str) == NULL)
			{
				printf("Arguments can only contain positive integers.\n");
				return (0);
			}
			str++;
		}
		i++;
	}
	return (1);
}

int	display_usage(void)
{
	printf("\nUsage : ./philo [number_of_philosophers] [time_to_die] ");
	printf("[time_to_eat] [time_to_sleep] [number_of_cycles]\n");
	printf("\n[number_of_cycles] is optional.\n");
	printf("All times are expressed in ms.\n");
	return (1);
}
