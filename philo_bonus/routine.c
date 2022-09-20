/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:08:56 by misrailo          #+#    #+#             */
/*   Updated: 2022/09/20 06:17:24 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_a_print(t_data *data, int num)

{
	if (num == 0)
	{
		sem_wait(data->outputting);
		printf("%ld %d has taken a fork\n",
			get_time() - data->birth, data->phil_id);
		sem_post(data->outputting);
	}
	if (num == 1)
	{
		sem_wait(data->outputting);
		printf("%ld %d is eating\n", get_time() - data->birth, data->phil_id);
		sem_post(data->outputting);
	}
	if (num == 2)
	{
		sem_wait(data->outputting);
		printf("%ld %d is sleeping\n", get_time() - data->birth, data->phil_id);
		sem_post(data->outputting);
	}
	if (num == 3)
	{
		sem_wait(data->outputting);
		printf("%ld %d is thinking\n", get_time() - data->birth, data->phil_id);
		sem_post(data->outputting);
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
			sem_wait(data->outputting);
			printf("%ld %d died\n", get_time() - data->birth, data->phil_id);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

void	routine_bonus(t_data *data)
{
	pthread_t	death;

	pthread_create(&death, NULL, *funeral, data);
	while (1)
	{
		sem_wait(data->fork);
		lock_a_print(data, 0);
		sem_wait(data->fork);
		lock_a_print(data, 1);
		ft_usleep(data->eat_time);
		data->starving = get_time();
		sem_post(data->fork);
		sem_post(data->fork);
		data->eat_nbr--;
		if (data->eat_nbr <= 0)
			exit (0);
		lock_a_print(data, 2);
		ft_usleep(data->sleep_time);
		lock_a_print(data, 3);
	}
	pthread_join(death, NULL);
	exit (0);
}

int	phils_forks(t_data *data, int i, int j)
{
	i = 0;
	while (i < data->av1)
	{
		j = fork();
		if (j == 0)
		{
			if (data[i].phil_id % 2 == 0)
				ft_usleep(data->eat_time / 10);
			data[i].birth = get_time();
			data[i].starving = get_time();
			routine_bonus(&data[i]);
		}
		else
			data->id[i] = j;
		i++;
	}
	wait(NULL);
	i = 0;
	while (i < data->av1)
	{
		kill(data->id[i], SIGINT);
		i++;
	}
	return (0);
}
