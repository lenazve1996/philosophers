/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:30:07 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/25 13:10:10 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_ph *ph)
{
	pthread_mutex_lock(ph->message);
	printf("%lld %d is eating\n", *ph->time - ph->zero_time, ph->id + 1);
	pthread_mutex_unlock(ph->message);
	my_usleep(ph->eat_time);
	pthread_mutex_lock(ph->message);
	ph->last_eat_timestamp = *ph->time;
	pthread_mutex_unlock(ph->message);
	pthread_mutex_lock(ph->meals);
	*ph->already_ate = *ph->already_ate + 1;
	pthread_mutex_unlock(ph->meals);
}

void	ft_sleep(t_ph *ph)
{
	long long	i;

	pthread_mutex_lock(ph->message);
	printf("%lld %d is sleeping\n", *ph->time - ph->zero_time, ph->id + 1);
	i = *ph->time - ph->zero_time;
	if (i < 0)
	{
		printf("*ph->time - %lld\n", *ph->time);
		printf("ph->zero_time - %lld\n", ph->zero_time);
	}
	pthread_mutex_unlock(ph->message);
	my_usleep(ph->sleep_time);
}

void	ft_think(t_ph *ph)
{
	pthread_mutex_lock(ph->message);
	printf("%lld %d is thinking\n", *ph->time - ph->zero_time, ph->id + 1);
	pthread_mutex_unlock(ph->message);
}

void	ft_take_forks(t_ph *ph)
{
	pthread_mutex_lock(ph->left_fork);
	pthread_mutex_lock(ph->message);
	printf("%lld %d has taken a fork\n", *ph->time - ph->zero_time, ph->id + 1);
	pthread_mutex_unlock(ph->message);
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(ph->message);
	printf("%lld %d has taken a fork\n", *ph->time - ph->zero_time, ph->id + 1);
	pthread_mutex_unlock(ph->message);
}

void	ft_put_forks(t_ph *ph)
{
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}
