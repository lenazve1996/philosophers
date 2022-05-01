/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:11:18 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/05/01 19:01:32 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_scan_death(t_lst *data)
{
	pthread_mutex_lock(data->message);
	if (data->philo_died == 1)
	{
		pthread_mutex_unlock(data->message);
		return (1);
	}
	pthread_mutex_unlock(data->message);
	return (0);
}

int	ft_check_death(t_lst *data, t_ph ph)
{
	pthread_mutex_lock(data->message);
	if (data->time - ph.last_dinner > data->die_time)
	{
		data->philo_died = 1;
		printf("%lld %d died\n", data->time - data->zero_time, ph.id + 1);
		pthread_mutex_unlock(data->message);
		return (1);
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

void	ft_monitoring(void *main_data)
{
	t_lst	*data;
	int		i;

	data = (t_lst *)main_data;
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
			if (ft_check_death(data, data->philo_specs[i]) == 1)
				return ;
			i++;
		}
	}
}

int	ft_wait_threads(t_lst *data)
{
	int	id;

	id = 0;
	while (id < data->numb)
	{
		if (pthread_join(data->philos[id], NULL) != 0)
		{
			return (ft_putstr_ret("Error: pthread_join failed\n", 2));
		}
		id++;
	}
	return (0);
}
