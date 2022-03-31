/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:24:01 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/31 13:48:03 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_check_death(t_lst *data)
{
	long long	time;

	time = find_current_time();
	if (time - data->last_meal > data->die_time)
	{
		sem_wait(data->messages);
		printf("%lld %d died\n", time - data->zero_time, data->id + 1);
		exit (3);
	}
}

void	*ft_monitoring(void *info)
{
	int		times_to_eat;
	t_lst	*data;

	data = (t_lst *)info;
	times_to_eat = data->numb * data->must_eat;
	while (1)
	{
		ft_check_death(data);
		usleep(250);
	}
	return (NULL);
}

int	ft_start_monitoring(t_lst *data)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, &ft_monitoring, data) != 0)
	{	
		return (ft_putstr_ret("pthread_create failed\n", 2));
	}
	if (pthread_detach(thread) != 0)
	{
		return (ft_putstr_ret("Error: pthread_detach failed\n", 2));
	}
	return (0);
}
