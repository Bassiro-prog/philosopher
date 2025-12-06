/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:17:49 by bnanque           #+#    #+#             */
/*   Updated: 2025/11/29 13:09:23 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	print_state(t_philo *philo, const char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (!*(philo->dead))
	{
		time = get_current_time();
		printf("%zu %d %s\n", time - philo->start_time, philo->id, str);
	}
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_unlock(philo->print_lock);
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start_time;
	size_t	elapsed;

	start_time = get_current_time();
	while (1)
	{
		elapsed = get_current_time() - start_time;
		if (elapsed >= milliseconds)
			break ;
		usleep((milliseconds - elapsed) * 9 / 10 * 1000);
	}
}

void	*monitor(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (1)
	{
		if (check_death(philos) == 1 || check_meals(philos) == 1)
			break ;
		usleep(1000);
	}
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
