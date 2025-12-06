/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:51:05 by bnanque           #+#    #+#             */
/*   Updated: 2025/11/29 13:09:53 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	int	dead;

	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal > time_to_die
		&& philo->eating == 0)
		dead = 1;
	else
		dead = 0;
	pthread_mutex_unlock(philo->meal_lock);
	if (dead)
		return (1);
	return (0);
}

int	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philo_dead(&philos[i], philos[i].time_to_die))
		{
			print_state(&philos[i], "died");
			pthread_mutex_lock(philos[i].dead_lock);
			*(philos[i].dead) = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_meals(t_philo *philos)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philos[0].meals_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meal_eating >= philos[i].meals_to_eat)
			finished++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*(philos[0].dead) = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	destroy_mutexes(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	if (str != NULL)
		write(2, str, ft_strlen(str));
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->print_lock);
	pthread_mutex_destroy(&program->meal_lock);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	philo_life_cycle(t_philo *philo)
{
	while (!*(philo->dead))
	{
		pthread_mutex_lock(philo->meal_lock);
		if (philo->meals_to_eat != -1
			&& philo->meal_eating >= philo->meals_to_eat)
		{
			pthread_mutex_unlock(philo->meal_lock);
			usleep(1000);
			continue ;
		}
		pthread_mutex_unlock(philo->meal_lock);
		take_forks(philo);
		philo_eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo_sleep(philo);
		philo_think(philo);
	}
}
