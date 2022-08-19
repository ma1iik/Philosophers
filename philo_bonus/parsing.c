/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:08:43 by misrailo          #+#    #+#             */
/*   Updated: 2022/08/19 14:08:44 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else if (c == '+' || c == '-')
		return (0);
	else
		return (1);
}

int	check_if_digit(int ac, char **av)
{
	int		i;
	int		j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]))
			{
				printf("Not number\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parsing(int ac, char **av)
{
	int		i;

	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) < 0 || ft_atoi(av[i]) >= MAX)
			return (1);
	}
	if (check_if_digit(ac, av))
		return (1);
	return (0);
}

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*dest;
	size_t			i;

	dest = s;
	i = 0;
	while (i < len)
	{
		*dest++ = c;
		i++;
	}
	return (s);
}
