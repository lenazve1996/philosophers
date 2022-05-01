/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:56:40 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/05/01 19:03:32 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./libft/libft_funcs.h"
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define PARSER_ERROR 5
# define MALLOC_ERROR 6
# define MUT_CREATE_ERROR 7
# define TAKE_FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4

typedef struct s_ph
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_dinner;
	int				cycles;
	void			*main_data;
}				t_ph;

typedef struct s_lst
{
	int				numb;
	pthread_t		*philos;
	pthread_t		monitor;
	pthread_mutex_t	*mut;
	pthread_mutex_t	*message;
	long long		zero_time;
	long long		time;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				already_ate;
	int				cycles;
	int				end;
	int				philo_died;
	t_ph			*philo_specs;
}				t_lst;

void		free_mut_array(t_lst *data, int free_numb);
int			ft_clearing(t_lst *data, int error_flag);
int			parser(int ac, char **av, t_lst *data);
void		ft_define_cycles_numb(t_lst *data);
void		ft_monitoring(void *main_data);
void		ft_initial_time(t_lst *data);
void		set_philo_specs(t_lst *data);
int			ft_run_threads(int id, t_lst *data);
int			ft_wait_threads(t_lst *data);
int			ft_scan_death(t_lst *data);
int			ft_check_death(t_lst *data, t_ph ph);
int			ft_eat(t_ph *ph, t_lst *data);
int			ft_sleep(t_ph *ph, t_lst *data);
int			ft_think(t_ph *ph, t_lst *data);
int			ft_take_forks(t_ph *ph, t_lst *data);
void		ft_put_forks(t_ph *ph);
void		my_usleep(long long msec);
long long	find_current_time(void);
int			ft_print_message(t_lst *data, t_ph *ph, int action);

#endif
