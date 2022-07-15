/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:28:03 by misrailo          #+#    #+#             */
/*   Updated: 2022/07/15 10:48:39 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phils_data(int ac, char **av, t_data *data)
{
	int		i;

	i = 0;
	pthread_mutex_init(&data->output, NULL);
	while (i < ft_atoi(av[1]))
	{
		data[i].av1 = ft_atoi(av[1]);
		data[i].phil_id = i + 1;
		data[i].death_time = ft_atoi(av[2]);
		data[i].eat_time = ft_atoi(av[3]);
		data[i].sleep_time = ft_atoi(av[4]);
		data[i].starving = 0;
		data[i].birth = 0;
		data[i].right_fork = 0;
		pthread_mutex_init(&data[i].left_fork, NULL);
		if (ac == 6)
			data[i].eat_nbr = ft_atoi(av[5]);
		else
			data[i].eat_nbr = MAX;
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

void	lock_a_print(t_data *data, int num)
{
	if (num == 0)
	{
		pthread_mutex_lock(&data->output);
		printf("%ld %d has taken a fork\n", get_time() - data->birth, data->phil_id);
		pthread_mutex_unlock(&data->output);
	}
	if (num == 1)
	{
		pthread_mutex_lock(&data->output);
		printf("%ld %d is eating\n", get_time() - data->birth, data->phil_id);
		pthread_mutex_unlock(&data->output);
	}
	if (num == 2)
	{
		pthread_mutex_lock(&data->output);
		printf("%ld %d is sleeping\n", get_time() - data->birth, data->phil_id);
		pthread_mutex_unlock(&data->output);
	}
	if (num == 3)
	{
		pthread_mutex_lock(&data->output);
		printf("%ld %d is thinking\n", get_time() - data->birth, data->phil_id);
		pthread_mutex_unlock(&data->output);
	}
}

void	*phils_routine(void *ptr)
{
	t_data	*data;

	data = ptr;
	if (data->phil_id % 2 == 0)
		ft_usleep(data->eat_time / 10);
	while (1)
	{
		if (data->phil_id == data->av1)
		{
			pthread_mutex_lock(data->right_fork);
			lock_a_print(data, 0);
			pthread_mutex_lock(&data->left_fork);
			lock_a_print(data, 1);
			ft_usleep(data->eat_time);
			data->starving = get_time();
			pthread_mutex_unlock(&data->left_fork);
			pthread_mutex_unlock(data->right_fork);
			data->eat_nbr--;
			lock_a_print(data, 2);
			ft_usleep(data->sleep_time);
			lock_a_print(data, 3);
		}
		else
		{
			pthread_mutex_lock(&data->left_fork);
			lock_a_print(data, 0);
			pthread_mutex_lock(data->right_fork);
			lock_a_print(data, 1);
			ft_usleep(data->eat_time);
			data->starving = get_time();
			pthread_mutex_unlock(data->right_fork);
			pthread_mutex_unlock(&data->left_fork);
			data->eat_nbr--;
			lock_a_print(data, 2);
			ft_usleep(data->sleep_time);
			lock_a_print(data, 3);
		}
	}
	return (NULL);
}

void	*funeral(void *ptr)
{
	t_data	*data;
	int		val;
	int		*result;

	data = ptr;
	val = 0;
	result = malloc(sizeof(int));
	while (1)
	{
		if (get_time() - data->starving > data->death_time)
		{
			pthread_mutex_lock(&data->output);
			printf("%ld P %d died\n", get_time() - data->birth, data->phil_id);
			val = 1;
			*result = val;
			return ((void *) result);
		}
		if (data->eat_nbr == 0)
		{
			*result = val;
			return ((void *) result);
		}
	}
}

void	phils_thread(char **argv, t_data *data)
{
	int			i;
	int			*res;
	pthread_t	death;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		data[i].birth = get_time();
		data[i].starving = get_time();
		pthread_create(&data[i].phil, NULL, &phils_routine, &data[i]);
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&death, NULL, &funeral, &data[i]);
		pthread_join(death, (void **) &res);
		if (*res == 1)
		{
			free(res);
			return ;
		}
		i++;
	}
	free(res);
	return ;
}

int	main(int ac, char **av)
{
	t_data		*data;

	data = ft_calloc(sizeof(t_data), ft_atoi(av[1]));
	parsing(ac, av);
	phils_data(ac, av, data);
	phils_thread(av, data);
	free(data);
}
