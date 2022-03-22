/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:06:21 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/22 21:24:27 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eating(t_lst *data, int n, sem_t *message)
{
	sem_wait(message);
	printf("%lld %d is eating\n", *data->cur_time - data->zero_time, n + 1);
	//printf("data->cur_time %lld\n", *data->cur_time);
	//printf("data->zero_time %lld\n", data->zero_time);
	sem_post(message);
	my_usleep(data->eat_time);
	//ph->last_eat_timestamp = data->cur_time;
	data->last_meal[n] = *data->cur_time;
	sem_wait(message);
	data->already_ate = data->already_ate + 1;
	sem_post(message);
}

void	ft_sleeping(t_lst *data, int n, sem_t *message)
{
	sem_wait(message);
	printf("%lld %d is sleeping\n", *data->cur_time - data->zero_time, n + 1);
	sem_post(message);
	my_usleep(data->sleep_time);
}

void	ft_thinking(t_lst *data, int n, sem_t *message)
{
	sem_wait(message);
	printf("%lld %d is thinking\n", *data->cur_time - data->zero_time, n + 1);
	sem_post(message);
}

void	ft_ph_take_forks(t_lst *data, int n, sem_t *message)
{
	sem_wait(message);
	printf("%lld %d has taken a fork\n", *data->cur_time - data->zero_time, n + 1);
	sem_post(message);
	sem_wait(message);
	printf("%lld %d has taken a fork\n", *data->cur_time - data->zero_time, n + 1);
	sem_post(message);
}

//void	ft_ph_put_forks(t_lst *data, int n, sem_t *message)
//{
//	//pthread_mutex_unlock(ph->left_fork);
//	//pthread_mutex_unlock(ph->right_fork);
//}