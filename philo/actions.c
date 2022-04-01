/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:30:07 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/04/01 12:38:52 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_ph *ph, t_lst *data)
{
	if (ft_print_message(data, ph, EAT) == 1)
		return (1);
	my_usleep(data->eat_time);
	pthread_mutex_lock(data->message);
	ph->last_dinner = data->time;
	++data->already_ate;
	if (data->already_ate == data->numb * data->must_eat)
		data->end = 1;
	pthread_mutex_unlock(data->message);
	return (0);
}

int	ft_sleep(t_ph *ph, t_lst *data)
{
	if (ft_print_message(data, ph, SLEEP) == 1)
		return (1);
	my_usleep(data->sleep_time);
	return (0);
}

int	ft_think(t_ph *ph, t_lst *data)
{
	if (ft_print_message(data, ph, THINK) == 1)
		return (1);
	return (0);
}

int	ft_take_forks(t_ph *ph, t_lst *data)
{
	pthread_mutex_lock(ph->left_fork);
	if (ft_print_message(data, ph, TAKE_FORK) == 1)
		return (1);
	if (data->numb == 1)
		return (1);
	pthread_mutex_lock(ph->right_fork);
	ft_print_message(data, ph, TAKE_FORK);
	return (0);
}

void	ft_put_forks(t_ph *ph)
{
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}
