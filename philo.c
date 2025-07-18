/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:43:29 by hboutale          #+#    #+#             */
/*   Updated: 2025/07/18 10:45:26 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	**init_philos(int n, t_app *app)
{
	t_philosopher	**philos;
	int				i;

	philos = malloc(sizeof(t_philosopher *) * n);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		philos[i] = init_philo(i + 1, app);
		if (!philos[i])
			return (free_philos_until(philos, n));
	}
	return (philos);
}

t_philosopher	*init_philo(int id, t_app *app)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->state = EATING;
	philo->last_meal = 0;
	philo->app = app;
	philo->num_eat = app->args->max_meals;
	return (philo);
}

void	*free_philos_until(t_philosopher **philo, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(philo[i++]);
	free(philo);
	return (NULL);
}
