/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 02:30:46 by misrailo          #+#    #+#             */
/*   Updated: 2022/08/19 14:14:29 by misrailo         ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>

# define MAX 2147483647

typedef struct s_data
{
	int				av1;
	int				phil_id;
	long int		death_time;
	long int		eat_time;
	long int		sleep_time;
	long int		birth;
	int				eat_nbr;
	int				starving;
	int				lunch_times_on;
	int				must_die;
	pthread_mutex_t	output;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		phil;
	sem_t			*fork;
	sem_t			*outputting;
	int				*id;
}	t_data;

int			parsing(int ac, char **av);
int			get_time(void);
void		ft_usleep(int ms);
int			ft_isneg(int x);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
int			ft_isdigit(int c);
int			check_if_digit(int ac, char **av);
void		*ft_memset(void *s, int c, size_t len);
void		phils_thread(char **argv, t_data *data);
void		*funeral(void *ptr);
void		*phils_routine(void *ptr);
void		last_phil_routine(t_data *data);
void		lock_a_print(t_data *data, int num);
int			routine_bonus(t_data *data);
int			phils_forks(t_data *data);

#endif
