/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:56:40 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/19 17:33:13 by ayajirob@st      ###   ########.fr       */
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


#endif
