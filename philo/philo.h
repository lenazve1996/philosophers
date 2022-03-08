#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include "./libft/libft_funcs.h"
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h> 

typedef struct	s_ph
{
	int				id;
	int				numb;
	pthread_mutex_t	*message;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	long long		zero_time;
	long long		last_dinner;
	int				die_time;
	int				eat_time;
	int 			sleep_time;
	int				must_eat;
}				t_ph;

typedef struct	s_lst
{
	int				numb;
	pthread_t		*philos;
	pthread_mutex_t *mut;
	int				die_time;
	int				eat_time;
	int 			sleep_time;
	int				must_eat;
	t_ph			*ph;
}				t_lst;

size_t	ft_strlen(const char *s);

#endif
