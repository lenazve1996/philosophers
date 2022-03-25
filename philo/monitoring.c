/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:11:18 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/25 21:55:06 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_death(t_lst *data, t_ph ph)
{
	pthread_mutex_lock(data->message);
	if (data->time - ph.last_dinner > data->die_time)
	{
		printf("%lld %d died\n", data->time - data->zero_time, ph.id + 1);
		return (ft_clearing(data, 1));
		//exit (1);
	}
	pthread_mutex_unlock(data->message);
	return (0);
}

static int	ft_check_meals_numb(t_lst *data)
{
	pthread_mutex_lock(data->message);
	if (data->end == 1)
	{
		return (1);
	}
	pthread_mutex_unlock(data->message);
	return (0);
}

void	ft_monitor_death(t_lst *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->numb)
		{
			pthread_mutex_lock(data->message);
			data->time = find_current_time();
			pthread_mutex_unlock(data->message);
			if (ft_check_meals_numb(data) == 1)
				return ;
			if (ft_check_death(data, data->ph[i]) == 1)
				return ;
			i++;
		}
	}
}
