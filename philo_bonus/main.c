/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:09:39 by misrailo          #+#    #+#             */
/*   Updated: 2022/08/19 17:01:21 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	init_forks(char **av, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < ft_atoi(av[1]))
// 	{
// 		if (i == 0)
// 			data[i].right_fork = &data[ft_atoi(av[1]) - 1].left_fork;
// 		else
// 			data[i].right_fork = &data[i - 1].left_fork;
// 		i++;
// 	}
// }

void	phils_data(int ac, char **av, t_data *data)
{
	int		i;

	i = 0;
	pthread_mutex_init(&data->output, NULL);
	while (i < ft_atoi(av[1]))
	{
		data[i].av1 = data->av1;
		data[i].phil_id = i + 1;
		data[i].death_time = ft_atoi(av[2]);
		data[i].eat_time = ft_atoi(av[3]);
		data[i].sleep_time = ft_atoi(av[4]);
		data[i].starving = 0;
		data[i].birth = 0;
		data[i].right_fork = 0;
		data[i].output = data->output;
		data[i].fork = data->fork;
		if (ac == 6)
			data[i].eat_nbr = ft_atoi(av[5]);
		else
			data[i].eat_nbr = MAX;
		i++;
	}
}

void	ft_free(t_data *data)
{
	int		i;

	i = 0;
	pthread_mutex_destroy(&data->output);
	while (i < data->av1)
	{
		pthread_mutex_destroy(&data[i].left_fork);
		i++;
	}
	free(data);
}

int	main(int ac, char **av)
{
	t_data		*data;

	data = ft_calloc(sizeof(t_data), ft_atoi(av[1]));
	data->id = ft_calloc(sizeof(data->id), ft_atoi(av[1]));
	if (ac != 5 && ac != 6)
		return (0);
	if (parsing(ac, av))
		return (0);
	sem_unlink("fork");
	sem_unlink("outputting");
	data->outputting = sem_open("outputting", O_CREAT, 0644, 1);
	data->fork = sem_open("fork", O_CREAT, 0644, ft_atoi(av[1]));
	data->av1 = ft_atoi(av[1]);
	phils_data(ac, av, data);
	phils_forks(data);
	//phils_thread(av, data);
	ft_free(data);
	return (0);
}

