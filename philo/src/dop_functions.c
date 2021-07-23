/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:00:50 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/06/29 00:01:09 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isnumber(char *str)
{
	char	*str1;

	str1 = str;
	while (*str1)
	{
		if (48 > *str1 || *str1 > 57)
			return (0);
		str1++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	atoi;
	int	k;

	k = 1;
	atoi = 0;
	while ((*str == ' ') || (*str == '\f') || (*str == '\r')
		   || (*str == '\t') || (*str == '\v') || (*str == '\n'))
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			k = -k;
		str++;
	}
	while ((*str >= '0') && (*str <= '9') && atoi <= 2147483647)
	{
		atoi = atoi * 10 + (*str - 48);
		str++;
	}
	if (atoi > 2147483647 && k == -1)
		return (53);
	if (atoi > 2147483647 && k == 1)
		return (-1);
	return (atoi * k);
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	message(t_phil_struct *phils, char *str)
{
	if (phils->init_data->end_flag == 1)
		return (1);
	if (pthread_mutex_lock(phils->init_data->for_print) != 0)
		return (0);
	printf(YELLOW"%ld %d %s\n", get_current_time() - phils->init_data->start,
		phils->id, str);
	if (pthread_mutex_unlock(phils->init_data->for_print) != 0)
		return (0);
	return (1);
}

int	checkargs(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isnumber(argv[i++]))
		{
			write(2, "The argument should be a number\n", 32);
			return (0);
		}
	}
	if (ft_atoi(argv[1]) < 1)
		return (0);
	return (1);
}
