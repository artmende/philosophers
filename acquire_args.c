/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:59:32 by artmende          #+#    #+#             */
/*   Updated: 2021/12/29 14:56:21 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	acquire_args(t_misc *misc, int argc, char **argv)
{
	if ((argc > 6 && printf("\nToo many arguments.\n"))
		|| (argc < 5 && printf("\nToo few arguments.\n"))
		|| check_args_only_nbr(argc, argv) == 0)
		return (0);
	misc->nbr_of_philo = ft_atoi(argv[1]);
	if ((misc->nbr_of_philo == 0 && printf("\nThere are no philosophers.\n"))
		|| ((misc->nbr_of_philo > 200 || misc->nbr_of_philo < 0)
			&& printf("\nMax 200 philos.\n")))
		return (0);
	misc->time_to_die = ft_atoi(argv[2]);
	misc->time_to_eat = ft_atoi(argv[3]);
	misc->time_to_sleep = ft_atoi(argv[4]);
	if ((misc->time_to_die < 60 || misc->time_to_eat < 60
			|| misc->time_to_sleep < 60)
		&& printf("\nAll times must be 60 ms minimum.\n"))
		return (0);
	if (argc == 6)
		misc->nbr_of_cycles = ft_atoi(argv[5]);
	else
		misc->nbr_of_cycles = -1;
	if (misc->nbr_of_cycles == 0 && printf("\n[number_of_cycles] is 0.\n"))
		return (0);
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
				printf("\nArguments can only contain positive integers.\n");
				return (0);
			}
			str++;
		}
		i++;
	}
	return (1);
}
