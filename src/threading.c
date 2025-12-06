/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:27:15 by bnanque           #+#    #+#             */
/*   Updated: 2025/11/25 15:34:19 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	start_philo_threads(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				philo_routine, &program->philos[i]) != 0)
		{
			destroy_mutexes("Error creating philosopher threads\n",
				program, forks);
			return (1);
		}
		i++;
	}
	usleep(1000);
	return (0);
}

static int	join_philo_threads(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
		{
			destroy_mutexes("Error joining philosopher threads\n",
				program, forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	handle_monitor(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor, program->philos) != 0)
	{
		destroy_mutexes("Error creating monitor thread\n", program, forks);
		return (1);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		destroy_mutexes("Error joining monitor thread\n", program, forks);
		return (1);
	}
	return (0);
}

int	create_threads(t_program *program, pthread_mutex_t *forks)
{
	if (start_philo_threads(program, forks) != 0)
		return (1);
	if (handle_monitor(program, forks) != 0)
		return (1);
	if (join_philo_threads(program, forks) != 0)
		return (1);
	return (0);
}
