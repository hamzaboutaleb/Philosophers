/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:39:58 by hboutale          #+#    #+#             */
/*   Updated: 2025/07/18 11:25:18 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
#define INT_MAX 0x7FFFFFFF
# define ERROR_MSG \
	"Usage: number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

# define NUM_HELPER_MUTEX 4
# define PRINT 0
# define DEATH 1
# define EAT 2
# define STATE 3

# define NUM_STATES 3
# define EATING 0
# define SLEEPING 1
# define THINKING 2

typedef struct s_args
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					max_meals;
}						t_args;

typedef struct s_app	t_app;

typedef struct s_philosopher
{
	int					id;
	size_t				last_meal;
	int					num_eat;
	int					state;
	t_app				*app;
}						t_philosopher;

typedef struct s_app
{
	pthread_mutex_t		**forks;
	t_philosopher		**philos;
	pthread_mutex_t		**mutex;
	int					is_running;
	t_args				*args;
}						t_app;

// -------------- utils.c ---------------
int						ft_atoi(char *s, int *err);
void					ft_usleep(size_t time, t_app *app);
int						max(int a, int b);
size_t					get_current_time(void);
void					ft_print_status(t_philosopher *philo,
							const char *status);
// -------------- parse_args.c ---------
int						parse_args(int ac, char **av, t_args *args);
// -------------- app.c ---------
void					*free_forks_until(pthread_mutex_t **mutex, int n);
pthread_mutex_t			**init_mutex(int n);
t_app					*init_app(t_args *args);
void					free_app(t_app *app);
// -------------- philo.c ---------------
t_philosopher			**init_philos(int n, t_app *app);
t_philosopher			*init_philo(int id, t_app *app);
void					*free_philos_until(t_philosopher **philo, int n);
// -------------- monitor.c -------------
void					monitor_philosophers(t_app *app);
//---------------- philo_routine.c ------
void					*philosopher_routine(void *arg);
void					ft_create_threads(t_app *app);
// -------------- state.c ---------------
int						is_running(t_app *app);
int						set_running(t_app *app, int status);
void					set_last_time_eat(t_philosopher *philo);
void					set_state(t_app *app, t_philosopher *p, int new_state);
int						get_state(t_app *app, t_philosopher *p);
#endif