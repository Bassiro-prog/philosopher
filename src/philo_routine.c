/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:32:03 by bnanque           #+#    #+#             */
/*   Updated: 2025/11/29 12:26:47 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat);
	philo_life_cycle(philo);
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "take a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "take a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "take a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "take a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	print_state(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->meal_eating++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
}

void	philo_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_state(philo, "is thinking");
	usleep(100);
}
