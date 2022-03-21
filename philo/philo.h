/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:56:40 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/21 19:09:48 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./libft/libft_funcs.h"
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h> 

typedef struct s_ph
{
	int				id;
	int				numb;
	pthread_mutex_t	*message;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		zero_time;
	long long		last_dinner;
	long long		last_eat_timestamp;
	long long		timestamp;
	long long		*time;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				cycles;
	int				*already_ate;
}				t_ph;

typedef struct s_lst
{
	int				numb;
	pthread_t		*philos;
	pthread_mutex_t	*mut;
	pthread_mutex_t	message;
	long long		zero_time;
	long long		time;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				already_ate;
	int				cycles;
	t_ph			*ph;
}				t_lst;

void		free_mut_array(t_lst *data, int free_numb);
int			ft_clearing(t_lst *data, int error_flag);

int			ft_parser(int ac, char **av, t_lst *data);
void		ft_define_cycles_numb(t_lst *data);

void		ft_monitor_death(t_lst *data);
void		ft_initial_time(t_lst *data);
void		ft_data_for_philo(t_lst *data);
int			ft_run_threads(int id, t_lst *data);

void		ft_eat(t_ph *ph);
void		ft_sleep(t_ph *ph);
void		ft_think(t_ph *ph);
void		ft_take_forks(t_ph *ph);
void		ft_put_forks(t_ph *ph);

void		my_usleep(long long msec);
long long	find_current_time(void);

#endif
