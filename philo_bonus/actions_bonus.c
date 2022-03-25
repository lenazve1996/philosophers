/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:06:21 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/24 16:46:07 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eating(t_lst *data)
{
	sem_wait(data->messages);
	printf("%lld %d is eating\n", *data->cur_time - data->zero_time, \
	data->id + 1);
	sem_post(data->messages);
	my_usleep(data->eat_time);
	data->last_meal[data->id] = *data->cur_time;
}

void	ft_sleeping(t_lst *data)
{
	sem_wait(data->messages);
	printf("%lld %d is sleeping\n", *data->cur_time - data->zero_time, \
	data->id + 1);
	sem_post(data->messages);
	my_usleep(data->sleep_time);
}

void	ft_thinking(t_lst *data)
{
	sem_wait(data->messages);
	printf("%lld %d is thinking\n", *data->cur_time - data->zero_time, \
	data->id + 1);
	sem_post(data->messages);
}

void	ft_ph_take_forks(t_lst *data)
{
	sem_wait(data->forks);
	sem_wait(data->messages);
	printf("%lld %d has taken a fork\n", *data->cur_time - data->zero_time, \
	data->id + 1);
	sem_post(data->messages);
	sem_wait(data->forks);
	sem_wait(data->messages);
	printf("%lld %d has taken a fork\n", *data->cur_time - data->zero_time, \
	data->id + 1);
	sem_post(data->messages);
}

void	ft_ph_put_forks(t_lst *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
	usleep(100);
}
