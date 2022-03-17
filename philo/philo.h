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
	long long		last;
	long long		last_eat_timestamp;
	long long		last_time;
	long long		timestamp;
	long long		*time;
	int				die_time;
	int				eat_time;
	int 			sleep_time;
	int				must_eat;
	int				*already_ate;
}				t_ph;

typedef struct	s_lst
{
	int				numb;
	pthread_t		*philos;
	pthread_mutex_t *mut;
	pthread_mutex_t message;
	long long		zero_time;
	long long		time;
	int				die_time;
	int				eat_time;
	int 			sleep_time;
	int				must_eat;
	int				already_ate; 
	t_ph			*ph;
}				t_lst;

size_t	ft_strlen(const char *s);

#endif
