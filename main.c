#include "philo.h"

int main(int ac, char **av)
{
    t_args args;
    if (!parse_args(ac, av, &args))
    {
        printf(ERROR_MSG);
        return (-1);
    }
    
}