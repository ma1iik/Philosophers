/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:57:13 by misrailo          #+#    #+#             */
/*   Updated: 2022/07/15 12:25:36 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isalpha(int c)
{
	if (!((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')))
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
			if (ft_isalpha(av[i][j]) == 1)
			{
				printf("Not number\n");
				exit (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	parsing(int ac, char **av)
{
	check_if_digit(ac, av);
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
