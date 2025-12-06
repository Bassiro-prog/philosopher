/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:42:24 by bnanque           #+#    #+#             */
/*   Updated: 2025/12/05 13:50:06 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	int				id;
	int				eating;
	int				meal_eating;
	int				meals_to_eat;
	int				num_of_philos;
	int				*dead;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;

}	t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
}	t_program;

int		check_valid_args(char **argv);
int		check_args(char *args);
int		ft_atoi(const char *str);
void	parse_input(t_philo *philo, char **argv);
void	init_forks(pthread_mutex_t *fork, int num_philos);
void	init_program(t_program *program);
void	init_philos(t_philo *philos, t_program *program,
			pthread_mutex_t *fork, char **argv);

size_t	get_current_time(void);
size_t	ft_strlen(char *str);
void	print_state(t_philo *philo, const char *str);
void	ft_usleep(size_t milliseconds);

void	*monitor(void *args);
void	philo_life_cycle(t_philo *philo);
void	*philo_routine(void *arg);
int		create_threads(t_program *program, pthread_mutex_t *forks);

int		philo_dead(t_philo *philo, size_t time_to_die);
int		check_death(t_philo *philo);
int		check_meals(t_philo *philos);

void	take_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

void	destroy_mutexes(char *str, t_program *program, pthread_mutex_t *forks);

#endif
