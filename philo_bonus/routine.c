/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:08:56 by misrailo          #+#    #+#             */
/*   Updated: 2022/08/19 14:09:15 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lock_a_print(t_data *data, int num)
{
	if (num == 0)
	{
		sem_wait(&data->outputting);
		printf("%ld %d has taken a fork\n",
			get_time() - data->birth, data->phil_id);
		sem_post(&data->outputting);
	}
	if (num == 1)
	{
		sem_wait(&data->outputting);
		printf("%ld %d is eating\n", get_time() - data->birth, data->phil_id);
		sem_post(&data->outputting);
	}
	if (num == 2)
	{
		sem_wait(&data->outputting);
		printf("%ld %d is sleeping\n", get_time() - data->birth, data->phil_id);
		sem_post(&data->outputting);
	}
	if (num == 3)
	{
		sem_wait(&data->outputting);
		printf("%ld %d is thinking\n", get_time() - data->birth, data->phil_id);
		sem_post(&data->outputting);
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

// void	phils_thread(char **argv, t_data *data)
// {
// 	int			i;
// 	int			*res;
// 	pthread_t	death;

// 	i = -1;
// 	while (++i < ft_atoi(argv[1]))
// 	{
// 		data[i].birth = get_time();
// 		data[i].starving = get_time();
// 		pthread_create(&data[i].phil, NULL, &phils_routine, &data[i]);
// 	}
// 	i = 0;
// 	while (i < ft_atoi(argv[1]))
// 	{
// 		pthread_create(&death, NULL, &funeral, &data[i]);
// 		pthread_join(death, (void **) &res);
// 		if (*res == 1)
// 		{
// 			free(res);
// 			return ;
// 		}
// 		i++;
// 	}
// 	free(res);
// 	return ;
// }

int	routine_bonus(t_data *data)
{
	while (1)
	{
		sem_wait(&data->fork);
		lock_a_print(data, 0);
		sem_wait(&data->fork);
		lock_a_print(data, 1);
		ft_usleep(data->eat_time);
		data->starving = get_time();
		sem_post(&data->fork);
		sem_post(&data->fork);
		data->eat_nbr--;
		lock_a_print(data, 2);
		ft_usleep(data->sleep_time);
		lock_a_print(data, 3);
	}
}

int	phils_forks(t_data *data)
{
	int			i;
	int			j;
	int			*res;
	pthread_t	death;

	while (i < data[i].av1)
	{
		j = fork();
		if (j == 0)
		{
			if (data[i].phil_id % 2 == 0)
				ft_usleep(data->eat_time / 10);
			routine_bonus(data);
		}
		else
			data[i].id = j;
		i++;
	}
	i = 0;
	while (i < ft_atoi(data[i].av1))
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
	wait(NULL);
	i = 0;
	while (i < data[i].av1)
	{
		kill(data[i].id, SIGINT);
		i++;
	}
	return (0);
}
