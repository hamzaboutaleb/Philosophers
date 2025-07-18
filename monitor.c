/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:10:14 by hboutale          #+#    #+#             */
/*   Updated: 2025/07/18 11:18:16 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_app *app)
{
	int	i;

	if (app->args->max_meals <= 0)
		return (0);
	i = 0;
	while (i < app->args->num_philo)
	{
		if (app->philos[i]->num_eat > 0)
			return (0);
		i++;
	}
	return (1);
}

static size_t	get_last_time_eat(t_philosopher *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(philo->app->mutex[EAT]);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->app->mutex[EAT]);
	return (last_meal);
}

void	monitor_philosophers(t_app *app)
{
	size_t	i;
	size_t	time;

	while (is_running(app))
	{
		if (check_meals(app))
		{
			set_running(app, FALSE);
			return ;
		}
		time = get_current_time();
		i = 0;
		while (i < app->args->num_philo && is_running(app))
		{
			if (time - get_last_time_eat(app->philos[i]) >= app->args->time_die)
			{
				ft_print_status(app->philos[i], "died");
				set_running(app, FALSE);
				return ;
			}
			i++;
		}
		usleep(10);
	}
}
