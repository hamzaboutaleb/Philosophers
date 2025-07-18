/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:18:37 by hboutale          #+#    #+#             */
/*   Updated: 2025/07/18 11:18:46 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_running(t_app *app)
{
	int	running;

	pthread_mutex_lock(app->mutex[DEATH]);
	running = app->is_running;
	pthread_mutex_unlock(app->mutex[DEATH]);
	return (running);
}

int	set_running(t_app *app, int status)
{
	pthread_mutex_lock(app->mutex[DEATH]);
	app->is_running = status;
	pthread_mutex_unlock(app->mutex[DEATH]);
	return (status);
}

void	set_last_time_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->app->mutex[EAT]);
	if (philo->num_eat != -1)
		philo->num_eat = max(philo->num_eat - 1, 0);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->app->mutex[EAT]);
}

void	set_state(t_app *app, t_philosopher *p, int new_state)
{
	pthread_mutex_lock(app->mutex[STATE]);
	p->state = new_state;
	pthread_mutex_unlock(app->mutex[STATE]);
}

int	get_state(t_app *app, t_philosopher *p)
{
	int	res;

	pthread_mutex_lock(app->mutex[STATE]);
	res = p->state;
	pthread_mutex_unlock(app->mutex[STATE]);
	return (res);
}
