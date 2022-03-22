/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:56:40 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/22 21:06:56 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "../philo/libft/libft_funcs.h"
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h> 
# include <semaphore.h> 
# include "../philo/philo.h" 

//typedef struct s_ph
//{
//	int				id;
//	int				numb;
//	pthread_mutex_t	*message;
//	pthread_mutex_t	*left_fork;
//	pthread_mutex_t	*right_fork;
//	long long		zero_time;
//	long long		last_dinner;
//	long long		last_eat_timestamp;
//	long long		timestamp;
//	long long		*time;
//	int				die_time;
//	int				eat_time;
//	int				sleep_time;
//	int				must_eat;
//	int				*already_ate;
//}				t_ph;

//typedef struct s_lst
//{
//	int				numb;
//	pthread_t		*philos;
//	pthread_mutex_t	*mut;
//	pthread_mutex_t	message;
//	long long		zero_time;
//	long long		time;
//	int				die_time;
//	int				eat_time;
//	int				sleep_time;
//	int				must_eat;
//	int				already_ate;
//	t_ph			*ph;
//}				t_lst;

void	ft_eating(t_lst *data, int n, sem_t *message);
void	ft_sleeping(t_lst *data, int n, sem_t *message);
void	ft_thinking(t_lst *data, int n, sem_t *message);
void	ft_ph_take_forks(t_lst *data, int n, sem_t *message);
void	*ft_monitoring(void *info);

//void	ft_ph_put_forks(t_lst *data, int n, sem_t *message);

#endif