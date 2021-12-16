/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:20:56 by artmende          #+#    #+#             */
/*   Updated: 2021/12/16 17:48:42 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	long int	result_l;
	int			minus;
	int			i;

	result_l = 0;
	minus = 1;
	while (str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	(void)(str && (*str == '-' || *str == '+') && str++ && *(str - 1) == '-'
		&& (minus = -1));
	while (str && *str == '0')
		str++;
	i = 0;
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		result_l = 10 * result_l + str[i] - '0';
		i++;
	}
	if (i > 19 || result_l < 0)
	{
		if (minus == -1)
			return (0);
		return (-1);
	}
	return ((int)(minus * result_l));
}
