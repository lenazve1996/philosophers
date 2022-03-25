/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:11:18 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/25 16:29:55 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_death(t_lst *data, t_ph ph)
{
	if (data->time - ph.last_eat_timestamp > data->die_time)
	{
		pthread_mutex_lock(&data->message);
		printf("%lld %d died\n", data->time - data->zero_time, ph.id + 1);
		return (1);
	}
	return (0);
}

static int	ft_check_meals_numb(t_lst *data, int times_to_eat)
{
	pthread_mutex_lock(&data->meals);
	if (data->must_eat != -1 && data->already_ate == times_to_eat)
	{
		pthread_mutex_lock(&data->message);
		return (1);
	}
	pthread_mutex_unlock(&data->meals);
	return (0);
}

void	ft_monitor_death(t_lst *data)
{
	int	i;
	int	times_to_eat;

	times_to_eat = data->numb * data->must_eat;
	while (1)
	{
		i = 0;
		while (i < data->numb)
		{
			pthread_mutex_lock(&data->message);
			data->time = find_current_time();
			pthread_mutex_unlock(&data->message);
			if (ft_check_meals_numb(data, times_to_eat) == 1)
				return ;
			if (ft_check_death(data, data->ph[i]) == 1)
				return ;
			i++;
		}
	}
}
