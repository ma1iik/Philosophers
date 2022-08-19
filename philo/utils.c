/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 06:29:10 by misrailo          #+#    #+#             */
/*   Updated: 2022/08/19 15:07:40 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = get_time();
	while ((get_time() - time) < ms)
		usleep(ms);
}

int	ft_isneg(int x)
{
	if (x == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long int	a;
	int					i;
	int					b;

	a = 0;
	b = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\t' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			b = b * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + (str[i] - 48);
		i++;
		if (a >= 922337203685477587)
			return (ft_isneg(b));
	}
	return (a * b);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	total;

	total = count * size;
	str = malloc(total);
	if (!str)
		return (NULL);
	ft_memset(str, 0, total);
	return (str);
}
