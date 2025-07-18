/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:11:53 by hboutale          #+#    #+#             */
/*   Updated: 2025/07/18 11:15:40 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philosopher *philo)
{
	t_app	*app;
	int		left_fork;
	int		right_fork;

	app = philo->app;
	left_fork = philo->id - 1;
	right_fork = philo->id % app->args->num_philo;
	pthread_mutex_lock(app->forks[left_fork]);
	ft_print_status(philo, "has taken a fork");
	if (left_fork == right_fork)
	{
		ft_usleep(app->args->time_die + 100, app);
		pthread_mutex_unlock(app->forks[left_fork]);
		return ;
	}
	pthread_mutex_lock(app->forks[right_fork]);
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "is eating");
	set_last_time_eat(philo);
	ft_usleep(app->args->time_eat, app);
	pthread_mutex_unlock(app->forks[left_fork]);
	pthread_mutex_unlock(app->forks[right_fork]);
}

static void	sleeping(t_philosopher *philo)
{
	t_app	*app;

	app = philo->app;
	ft_print_status(philo, "is sleeping");
	ft_usleep(app->args->time_sleep, app);
}

static void	thinking(t_philosopher *philo)
{
	t_app	*app;

	app = philo->app;
	ft_print_status(philo, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_app			*app;
	int				i;
	void			(*fn[3])(t_philosopher *);

	philo = (t_philosopher *)arg;
	app = philo->app;
	if (philo->id % 2 == 0)
	{
		set_state(app, philo, THINKING);
		usleep(100);
	}
	fn[0] = eating;
	fn[1] = sleeping;
	fn[2] = thinking;
	while (TRUE)
	{
		if (!is_running(app))
			return (NULL);
		fn[philo->state](philo);
		set_state(app, philo, (philo->state + 1) % NUM_STATES);
	}
}

void	ft_create_threads(t_app *app)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * app->args->num_philo);
	if (!threads)
		return ;
	i = 0;
	while (i < app->args->num_philo)
	{
		app->philos[i]->last_meal = 0;
		if (pthread_create(&threads[i], NULL, philosopher_routine,
				app->philos[i]))
		{
			free(threads);
			return ;
		}
		i++;
	}
	monitor_philosophers(app);
	i = 0;
	while (i < app->args->num_philo)
		pthread_join(threads[i++], NULL);
	free(threads);
}
