#include "philo.h"

int parse_args(int ac, char **av, t_args *args)
{
    if (ac != 5 && ac != 6)
        return (FALSE);
    int err;
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
    if (ac == 6)
    {
        args->num_time_eat = ft_atoi(av[5], &err);
        if (err || args->num_time_eat < 0)
            return (FALSE);
    }
    return (TRUE);
}
