/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:56:40 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/23 21:21:01 by ayajirob@st      ###   ########.fr       */
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

typedef struct s_lst
{
	int				numb;
	int				id;
	sem_t			*messages;
	sem_t			*forks;
	int				*children_pids;
	long long		zero_time;
	long long		*cur_time;
	long long		*last_meal;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				cycles;
}				t_lst;

void	ft_eating(t_lst *data);
void	ft_sleeping(t_lst *data);
void	ft_thinking(t_lst *data);
void	ft_ph_take_forks(t_lst *data);
void	*ft_monitoring(void *info);
void	ft_ph_put_forks(t_lst *data);

long long	find_current_time(void);
void		my_usleep(long long msec);

void	ft_define_cycles_numb(t_lst *data);
//void	ft_ph_put_forks(t_lst *data, int n, sem_t *message);

#endif
