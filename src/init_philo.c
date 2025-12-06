/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:45:17 by bnanque           #+#    #+#             */
/*   Updated: 2025/12/05 13:49:51 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->meals_to_eat = ft_atoi(argv[5]);
	else
		philo->meals_to_eat = -1;
}

void	init_forks(pthread_mutex_t *fork, int num_philos)
{
	int	i;

	i = 0 ;
	while (i < num_philos)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}

void	init_program(t_program *program)
{
	program->dead_flag = 0;
	pthread_mutex_init(&program->print_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}

void	init_philos(t_philo *philos, t_program
*program, pthread_mutex_t *fork, char **argv)
{
	int		i;
	int		args;

	i = 0;
	args = ft_atoi(argv[1]);
	while (i < args)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meal_eating = 0;
		parse_input(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].print_lock = &program->print_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].left_fork = &fork[i];
		philos[i].right_fork = &fork[(i + 1) % args];
		i++;
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((size_t)time.tv_sec * 1000 + (size_t)time.tv_usec / 1000);
}
