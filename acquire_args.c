/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:59:32 by artmende          #+#    #+#             */
/*   Updated: 2021/12/28 15:42:18 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	acquire_args(t_misc *misc, int argc, char **argv)
{
	if (argc > 6 || argc < 5 || check_args_only_nbr(argc, argv) == 0)
		return (0);
	misc->nbr_of_philo = ft_atoi(argv[1]);
	if ((misc->nbr_of_philo == 0 && printf("\nThere are no philosophers.\n"))
		|| ((misc->nbr_of_philo > 200 || misc->nbr_of_philo < 0)
			&& printf("\nMax 200 philos.\n")))
		return (0);
	misc->time_to_die = ft_atoi(argv[2]);
	misc->time_to_eat = ft_atoi(argv[3]);
	misc->time_to_sleep = ft_atoi(argv[4]);
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
