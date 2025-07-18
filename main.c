/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:51:57 by hboutale          #+#    #+#             */
/*   Updated: 2025/07/18 11:18:36 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;
	t_app	*app;

	if (!parse_args(ac, av, &args))
	{
		printf(ERROR_MSG);
		return (1);
	}
	app = init_app(&args);
	if (!app)
	{
		printf("Error initializing application.\n");
		return (1);
	}
	ft_create_threads(app);
	free_app(app);
	return (0);
}
