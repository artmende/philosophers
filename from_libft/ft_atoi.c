/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:20:56 by artmende          #+#    #+#             */
/*   Updated: 2021/12/13 17:58:33 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
	ft_atoi has been modified a little bit to look for int overflows.
*/

int	ft_atoi(const char *str)
{
	long int	result_l;
	int			minus;
	int			i;

	result_l = 0;
	minus = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result_l = 10 * result_l + str[i] - '0';
		i++;
	}
	if (i > 10 || (i == 10 && *str > '2')
		|| (minus == 1 && result_l > 2147483647)
		|| (minus == -1 && result_l > 2147483648))
		return (0);
	return ((int)(minus * result_l));
}

int	main(int argc, char **argv)
{


//	printf("%d\n", ft_atoi(argv[1]));
//	printf("%d\n", atoi(argv[1]));

}
