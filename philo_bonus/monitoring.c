/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:24:01 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/23 21:19:10 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_check_death(t_lst *data, long long last_meal)
{
	if (*data->cur_time - last_meal > data->die_time)
	{
		sem_wait(data->messages);
		printf("%lld %d died\n", *data->cur_time - data->zero_time, data->id + 1);
		exit (3);
	}
}

void	*ft_monitoring(void *info)
{
	int	i;
	int	times_to_eat;

	t_lst *data = (t_lst *)info;
	times_to_eat = data->numb * data->must_eat;
	while (1)
	{
		i = 0;
		*data->cur_time = find_current_time();
		ft_check_death(data, data->last_meal[data->id]);
		i++;
	}
	return (NULL);
}