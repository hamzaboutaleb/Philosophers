#include "philo.h"

t_app *init_app(t_args *args)
{
    t_app *app;

    app = malloc(sizeof(t_app));
    if (!app)
        return (NULL);
    app->args = args;
    app->mutex = init_mutex(NUM_STATE);
    if (!app->mutex)
    {
        free_forks_until(app->mutex, NUM_STATE);
        return (free(app), NULL);
    }
    app->forks = init_mutex(args->num_philo);
    if (!app->forks)
        return (free(app), NULL);
    app->philos = init_philos(args->num_philo, app);
    if (!app->philos)
    {
        free_forks_until(app->forks, args->num_philo);
        free_forks_until(app->mutex, NUM_STATE);
        return (free(app), NULL);
    }
    return app;
}

void free_app(t_app *app)
{
    free_forks_until(app->forks, app->args->num_philo);
    free_philos_until(app->philos, app->args->num_philo);
    free_forks_until(app->mutex, NUM_STATE);
    free(app);
}

pthread_mutex_t **init_mutex(int n)
{
    pthread_mutex_t **mutex;
    mutex = malloc(sizeof(pthread_mutex_t *) * n);
    if (!mutex)
        return NULL;
    int i = 0;
    while (i < n)
    {
        if (pthread_mutex_init(mutex[i], NULL))
            return free_forks_until(mutex, i);
    }
    return mutex;
}

void *free_forks_until(pthread_mutex_t **mutex, int n)
{
    int i;

    i = 0;
    while (i < n)
        pthread_mutex_destroy(mutex[i++]);
    free(mutex);
    return (NULL);
}

t_philospher **init_philos(int n, t_args *args)
{
    t_philospher **philos;
    int i;

    philos = malloc(sizeof(t_philospher *) * n);
    if (!philos)
        return (NULL);
    i = 0;
    while (i < n)
    {
        philos[i] = init_philo(i, args->num_time_eat, args);
        if (!philos[i])
            return free_philos_until(philos, i);
    }
    return philos;
}

t_philospher *init_philo(int id, int num_eat, t_app *app)
{
    t_philospher *philo;

    philo = malloc(sizeof(t_philospher));
    if (!philo)
        return (NULL);
    philo->id = id;
    philo->last_meal = 0;
    philo->app = app;
    philo->num_eat = num_eat;
    return philo;
}

void *free_philos_until(pthread_mutex_t **philo, int n)
{
    int i;

    i = 0;
    while (i < n)
        free(philo[i++]);
    free(philo);
    return (NULL);
}