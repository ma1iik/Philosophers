/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:28:03 by misrailo          #+#    #+#             */
/*   Updated: 2022/07/12 09:33:17 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phils_data(int ac, char **av, t_data *data)
{
	int		i;

	i = 0;
	data->av1 = ft_atoi(av[1]);
	pthread_mutex_init(&data->output, NULL);
	while (i < ft_atoi(av[1]))
	{
		data[i].phil_id = i + 1;
		data[i].death_time = ft_atoi(av[2]);
		data[i].eat_time = ft_atoi(av[3]);
		data[i].sleep_time = ft_atoi(av[4]);
		data[i].starving = 0;
		data[i].birth = 0;
		pthread_mutex_init(&data[i].left_fork, NULL);
		if (ac == 6)
		{
			data[i].lunch_times_on = 1;
			data[i].eat_nbr = ft_atoi(av[5]);
		}
		else
			data[i].lunch_times_on = 0;
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (i == 0)
			data[i].right_fork = &data[ft_atoi(av[1]) - 1].left_fork;
		else
			data[i].right_fork = &data[i - 1].left_fork;
		i++;
	}
}

void	routine(t_data *data)
{
	pthread_mutex_lock(&data->left_fork);
	pthread_mutex_lock(&data->output);
	printf("Philosopher %d has taken fork\n", data->phil_id);
	pthread_mutex_unlock(&data->output);
	pthread_mutex_lock(data->right_fork);
	pthread_mutex_lock(&data->output);
	printf("Philosopher %d is eating\n", data->phil_id);
	pthread_mutex_unlock(&data->output);
	ft_usleep(data->eat_time);
	data->starving = get_time();
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(&data->left_fork);
	// if (data->lunch_times_on == 1)
	// {
	// 	data->eat_nbr--;
	// 	printf("\nPhil [%d] needs to eat [%d] more times\n\n", data->phil_id, data->eat_nbr);
	// }
	pthread_mutex_lock(&data->output);
	printf("Philosopher %d is sleeping\n", data->phil_id);
	pthread_mutex_unlock(&data->output);
	ft_usleep(data->sleep_time);
	pthread_mutex_lock(&data->output);
	printf("Philosopher %d is thinking\n", data->phil_id);
	pthread_mutex_unlock(&data->output);
}

void	routine1(t_data *data)
{
	pthread_mutex_lock(data->right_fork);
	pthread_mutex_lock(&data->output);
	printf("Philosopher %d has taken fork\n", data->phil_id);
	pthread_mutex_unlock(&data->output);
	pthread_mutex_lock(&data->left_fork);
	pthread_mutex_lock(&data->output);
	printf("Philosopher %d is eating\n", data->phil_id);
	pthread_mutex_unlock(&data->output);
	ft_usleep(data->eat_time);
	data->starving = get_time();
	pthread_mutex_unlock(&data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	if (data->lunch_times_on == 1)
	{
		data->eat_nbr--;
		printf("\nPhil [%d] needs to eat [%d] more times\n\n", data->phil_id, data->eat_nbr);
	}
	pthread_mutex_lock(&data->output);
	printf("Philosopher %d is sleeping\n", data->phil_id);
	pthread_mutex_unlock(&data->output);
	ft_usleep(data->sleep_time);
	pthread_mutex_lock(&data->output);
	printf("Philosopher %d is thinking\n", data->phil_id);
	pthread_mutex_unlock(&data->output);
}

void	*phils_routine(void *ptr) 
{
	t_data	*data;

	data = ptr;
	while (1)
	{
		if (data->lunch_times_on == 1 && data->eat_nbr == 0)
			return (0);
		if (data->phil_id % 2 == 0)
			usleep(data->eat_time / 10);
		// if (data->phil_id == data->av1)
		// 	routine1(data);
		// else
		pthread_mutex_lock(&data->left_fork);
		pthread_mutex_lock(&data->output);
		printf("Philosopher %d has taken fork\n", data->phil_id);
		pthread_mutex_unlock(&data->output);
		pthread_mutex_lock(data->right_fork);
		pthread_mutex_lock(&data->output);
		printf("Philosopher %d is eating\n", data->phil_id);
		pthread_mutex_unlock(&data->output);
		ft_usleep(data->eat_time);
		data->starving = get_time();
		pthread_mutex_unlock(data->right_fork);
		pthread_mutex_unlock(&data->left_fork);
		if (data->lunch_times_on == 1)
		{
			data->eat_nbr--;
			printf("\nPhil [%d] needs to eat [%d] more times\n\n", data->phil_id, data->eat_nbr);
		}
		pthread_mutex_lock(&data->output);
		printf("Philosopher %d is sleeping\n", data->phil_id);
		pthread_mutex_unlock(&data->output);
		ft_usleep(data->sleep_time);
		pthread_mutex_lock(&data->output);
		printf("Philosopher %d is thinking\n", data->phil_id);
		pthread_mutex_unlock(&data->output);
	}
}

void	*funeral(void *ptr)
{
	t_data	*data;
	int		i;

	data = ptr;
	i = 0;
	while (1)
	{
		if (get_time() - data->starving >= data->death_time)
		{
			pthread_mutex_lock(&data->output);
			printf("[%ld] Philosopher %d died\n", get_time() - data->birth, data->phil_id);
			return (0);
		}
		// if (data->lunch_times_on == 1)
		// {
		// 	if (data->eat_nbr == 0)
		// 		return (0);
		// }
	}
	return (0);
}

void	phils_thread(char **argv, t_data *data)
{
	int			i;
	pthread_t	death;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		data[i].birth = get_time();
		data[i].starving = get_time();
		pthread_create(&data[i].phil, NULL, &phils_routine, &data[i]);
		i++;
	}
	i = 0;
	while (i < data[i].av1)
	{
		pthread_create(&death, NULL, &funeral, &data[i]);
		pthread_join(death, NULL);
		i++;
	}
	// while (i < ft_atoi(argv[1]))
	// {
	// 	pthread_join(data[i].phil, NULL);
	// 	i++;
	// }
}

int	main(int ac, char **av)
{
	t_data		*data;

	data = ft_calloc(sizeof(t_data), ft_atoi(av[1]));
	parsing(ac, av);
	phils_data(ac, av, data);
	phils_thread(av, data);
	printf("%d is the launch nbr left\n", data->eat_nbr);
	free(data);
}
