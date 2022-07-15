/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:01:49 by misrailo          #+#    #+#             */
/*   Updated: 2022/07/15 13:02:15 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_a_print(t_data *data, int num)
{
	if (num == 0)
	{
		pthread_mutex_lock(&data->output);
		printf("%ld %d has taken a fork\n",
			get_time() - data->birth, data->phil_id);
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

void	last_phil_routine(t_data *data)
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

void	*phils_routine(void *ptr)
{
	t_data	*data;

	data = ptr;
	if (data->phil_id % 2 == 0)
		ft_usleep(data->eat_time / 10);
	while (1)
	{
		if (data->phil_id == data->av1)
			last_phil_routine(data);
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
