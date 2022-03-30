/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:24:01 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/30 17:50:21 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_check_death(t_lst *data)
{
	//printf("%p data->messages\n", data->messages);
	sem_wait(data->messages);
	if (*data->cur_time - data->last_meal > data->die_time)
	{
		//printf("*data->cur_time %lld\n", *data->cur_time);
		//printf("data->last_meal %lld\n", data->last_meal);
		//printf("data->die_time %d\n", data->die_time);
		//printf("%d value of sem_wait\n", sem_wait(data->messages));
		printf("%lld %d died\n", *data->cur_time - data->zero_time, data->id + 1);
		exit (3);
	}
	sem_post(data->messages);
}

void	*ft_monitoring(void *info)
{
	int		times_to_eat;
	t_lst	*data;

	data = (t_lst *)info;
	times_to_eat = data->numb * data->must_eat;
	while (1)
	{
		*data->cur_time = find_current_time();
		ft_check_death(data);
	}
	return (NULL);
}

int	ft_create_thread(t_lst *data)
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
	//ft_initial_time(data);
	return (0);
}
