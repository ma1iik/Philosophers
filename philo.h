/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 02:30:46 by misrailo          #+#    #+#             */
/*   Updated: 2022/07/15 10:55:49 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

# define MAX 2147483647

typedef struct s_data
{
	char			**argvs;
	int				phil_id;
	long int		death_time;
	long int		eat_time;
	long int		sleep_time;
	int				eat_nbr;
	long int		birth;
	int				starving;
	int				lunch_times_on;
	int				must_die;
	pthread_mutex_t	output;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		phil;
	int				av1;
}	t_data;

void	parsing(int ac, char **av);
int		get_time(void);
void	ft_usleep(int ms);

#endif
