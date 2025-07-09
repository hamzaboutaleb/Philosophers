#include "philo.h"

int ft_atoi(char *s, int *err)
{
    int result = 0;
    int sign = 1;
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

    return result * sign;
}
