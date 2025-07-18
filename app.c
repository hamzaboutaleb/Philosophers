/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:39:30 by hboutale          #+#    #+#             */
/*   Updated: 2025/07/18 10:43:54 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_app	*init_app(t_args *args)
{
	t_app	*app;

	app = malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->args = args;
	app->is_running = TRUE;
	app->mutex = init_mutex(NUM_HELPER_MUTEX);
	if (!app->mutex)
		return (free(app), NULL);
	app->forks = init_mutex(args->num_philo);
	if (!app->forks)
	{
		free_forks_until(app->mutex, NUM_HELPER_MUTEX);
		return (free(app), NULL);
	}
	app->philos = init_philos(args->num_philo, app);
	if (!app->philos)
	{
		free_forks_until(app->forks, args->num_philo);
		free_forks_until(app->mutex, NUM_HELPER_MUTEX);
		return (free(app), NULL);
	}
	return (app);
}

void	free_app(t_app *app)
{
	free_forks_until(app->forks, app->args->num_philo);
	free_philos_until(app->philos, app->args->num_philo);
	free_forks_until(app->mutex, NUM_HELPER_MUTEX);
	free(app);
}

pthread_mutex_t	**init_mutex(int n)
{
	pthread_mutex_t	**mutex;
	int				i;

	mutex = malloc(sizeof(pthread_mutex_t *) * n);
	if (!mutex)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		mutex[i] = malloc(sizeof(pthread_mutex_t));
		if (!mutex[i])
			return (free_forks_until(mutex, i));
	}
	i = -1;
	while (++i < n)
	{
		if (pthread_mutex_init(mutex[i], NULL))
			return (free_forks_until(mutex, n));
	}
	return (mutex);
}

void	*free_forks_until(pthread_mutex_t **mutex, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(mutex[i]);
		pthread_mutex_destroy(mutex[i++]);
	}
	free(mutex);
	return (NULL);
}
