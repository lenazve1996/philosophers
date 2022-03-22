/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:24:01 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/22 21:10:18 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//static int	ft_check_death(t_lst *data, long long last_meal)
//{
//	if (data->cur_time - last_meal > data->die_time)
//	{
//		printf("here2\n");
//		printf("data->cur_time %lld \n", data->cur_time);
//		printf("last_meal %lld \n", last_meal);
//		printf("%lld died\n", data->cur_time - data->zero_time/*, .id + 1*/);
//		return (1);
//	}
//	return (0);
//}

static int	ft_check_meals_numb(t_lst *data, int times_to_eat)
{
	if (data->must_eat != -1 && data->already_ate == times_to_eat)
	{
		printf("here1\n");
		return (1);
	}
	return (0);
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
		while (i < data->numb)
		{
			*data->cur_time = find_current_time();
			//printf("data->cur_time %lld\n", data->cur_time);
			if (ft_check_meals_numb(data, times_to_eat) == 1)
				return (NULL);
			//if (ft_check_death(data, data->last_meal[i]) == 1)
				//return (NULL);
			i++;
		}
	}
	return (NULL);
}