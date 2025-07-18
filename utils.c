/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:39:38 by hboutale          #+#    #+#             */
/*   Updated: 2025/07/18 11:17:07 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s, int *err)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	*err = FALSE;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (*err = TRUE, 0);
		if ((INT_MAX - (*s - '0')) / 10 < result)
			return (*err = TRUE, 0);
		result = result * 10 + (*s - '0');
		s++;
	}
	return (result * sign);
}

void	ft_usleep(size_t time, t_app *app)
{
	long	start;
	long	sleep_interval;

	start = get_current_time();
	if (app->args->num_philo > 100)
		sleep_interval = 500;
	else if (app->args->num_philo > 50)
		sleep_interval = 100;
	else
		sleep_interval = 50;
	while ((get_current_time() - start) < time)
		usleep(sleep_interval);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	get_current_time(void)
{
	struct timeval	tv;
	static size_t	start_time;

	gettimeofday(&tv, NULL);
	if (start_time == 0)
		start_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
}

void	ft_print_status(t_philosopher *philo, const char *status)
{
	if (!is_running(philo->app))
		return ;
	pthread_mutex_lock(philo->app->mutex[PRINT]);
	printf("%zu %d %s\n", get_current_time(), philo->id, status);
	pthread_mutex_unlock(philo->app->mutex[PRINT]);
}
