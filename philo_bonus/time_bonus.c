/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:34:22 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/30 18:22:41 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	find_current_time(void)
{
	struct timeval	cur_time;
	long long		time_now;

	gettimeofday(&cur_time, NULL);
	time_now = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
	return (time_now);
}

void	ft_initial_time(t_lst *data)
{
	data->zero_time = find_current_time();
	data->last_meal = data->zero_time;
}

void	my_usleep(long long msec)
{
	struct timeval				cur_time;
	unsigned long long			start_time;
	unsigned long long			end_time;
	unsigned long long			comparison;

	end_time = 0;
	start_time = find_current_time();
	comparison = start_time + msec;
	if (msec == 0)
		return ;
	if (msec != 1)
		usleep(1000 * msec - 2000);
	while (1)
	{
		gettimeofday(&cur_time, NULL);
		end_time = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
		if (end_time >= comparison)
		{
			return ;
		}
		usleep(250);
	}
}