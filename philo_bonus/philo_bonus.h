/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:56:40 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/04/27 20:49:59 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "../philo/libft/libft_funcs.h"
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h> 
# include <signal.h>
# include <semaphore.h>

# define TAKE_FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 3
# define PHILO_DIED 4
# define PHILO_ATE_ENOUGH 0
# define RETURN_FAILURE 1
# define RETURN_SUCCESS 0

typedef struct s_lst
{
	int				numb;
	int				id;
	sem_t			*messages;
	sem_t			*forks;
	sem_t			*general;
	int				*children_pids;
	long long		zero_time;
	long long		last_meal;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				cycles;
}				t_lst;

void		ft_eating(t_lst *data);
void		ft_sleeping(t_lst *data);
void		ft_ph_take_forks(t_lst *data);
void		*ft_monitoring(void *info);
int			ft_start_monitoring(t_lst *data);
void		ft_ph_put_forks(t_lst *data);
long long	find_current_time(void);
void		my_usleep(long long msec);
void		ft_define_cycles_numb(t_lst *data);
int			ft_parser(int ac, char **av, t_lst *data);
void		ft_initial_time(t_lst *data);
void		ft_cleaning(t_lst *data);
void		ft_wait_philos(t_lst *data);
int			ft_allocate_memory(t_lst *data);
int			ft_create_semaphores(t_lst *data);
void		ft_print_message(t_lst *data, int action);

#endif
