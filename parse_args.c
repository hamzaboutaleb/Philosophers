/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:39:50 by hboutale          #+#    #+#             */
/*   Updated: 2025/07/18 10:39:53 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int ac, char **av, t_args *args)
{
	int	err;

	if (ac != 5 && ac != 6)
		return (FALSE);
	args->num_philo = ft_atoi(av[1], &err);
	if (err || args->num_philo <= 0)
		return (FALSE);
	args->time_die = ft_atoi(av[2], &err);
	if (err || args->time_die < 0)
		return (FALSE);
	args->time_eat = ft_atoi(av[3], &err);
	if (err || args->time_eat < 0)
		return (FALSE);
	args->time_sleep = ft_atoi(av[4], &err);
	if (err || args->time_sleep < 0)
		return (FALSE);
	args->max_meals = -1;
	if (ac == 6)
	{
		args->max_meals = ft_atoi(av[5], &err);
		if (err || args->max_meals < 0)
			return (FALSE);
	}
	return (TRUE);
}
