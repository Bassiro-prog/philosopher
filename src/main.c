/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:46:00 by bnanque           #+#    #+#             */
/*   Updated: 2025/12/05 13:48:50 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] < '0' || args[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_args(argv[1]) == 1)
		return (write(2, "Invalid number of philosopher\n", 30), 1);
	if (ft_atoi(argv[2]) <= 0 || check_args(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 20), 1);
	if (ft_atoi(argv[3]) <= 0 || check_args(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 20), 1);
	if (ft_atoi(argv[4]) <= 0 || check_args(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 22), 1);
	if (argv[5] && (check_args(argv[5]) == 1 || ft_atoi(argv[5]) <= 0))
		return (write(2, "Invalid must eat value\n", 23), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (write(2, "invalid argument of count\n", 26), 1);
	if (check_valid_args(argv))
		return (1);
	program.philos = philo;
	init_program(&program);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philo, &program, forks, argv);
	if (create_threads(&program, forks) != 0)
		return (1);
	destroy_mutexes(NULL, &program, forks);
	return (0);
}
