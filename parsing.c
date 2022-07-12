/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:57:13 by misrailo          #+#    #+#             */
/*   Updated: 2022/06/30 15:39:25 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			printf("%c\n", av[i][j]);
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
	if (ac != 5 && ac != 6)
	{
		ft_printf("Error\n");
		exit (EXIT_FAILURE);
	}
	check_if_digit(ac, av);
}
