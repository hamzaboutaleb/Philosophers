#ifndef PHILO_H
#define PHILO_H
#include "stdio.h"
#include "limits.h"
#include "pthread.h"
#include "stdlib.h"

#define TRUE 1
#define FALSE 0
#define ERROR_MSG "Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

#define NUM_STATE 4
#define FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3

typedef struct s_args
{
    int num_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int num_time_eat;
} t_args;

typedef struct s_philosopher
{
    int id;
    size_t last_meal;
    int num_eat;
    t_app *app;
} t_philospher;

typedef struct s_app
{
    pthread_mutex_t **forks;
    t_philospher **philos;
    pthread_mutex_t **mutex;
    t_args *args;
} t_app;

// -------------- atoi.c ---------------
int ft_atoi(char *s, int *err);
// -------------- parse_args.c ---------
int parse_args(int ac, char **av, t_args *args);
// -------------- app.c ---------

#endif