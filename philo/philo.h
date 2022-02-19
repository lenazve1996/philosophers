#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>

typedef struct	s_lst
{
	int	philo;
	int	die_time;
	int	eat_time;
	int sleep_time;
	int	must_eat;

}				t_lst;

size_t	ft_strlen(const char *s);

#endif