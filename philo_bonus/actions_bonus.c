/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:06:21 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/04/01 12:58:21 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print_message(t_lst *data, int action)
{
	long long	time;
	int			id;

	id = data->id + 1;
	sem_wait(data->messages);
	time = find_current_time();
	if (action == TAKE_FORK)
		printf("%lld %d has taken a fork\n", time - data->zero_time, id);
	else if (action == EAT)
		printf("%lld %d is eating\n", time - data->zero_time, id);
	else if (action == SLEEP)
		printf("%lld %d is sleeping\n", time - data->zero_time, id);
	else if (action == THINK)
		printf("%lld %d is thinking\n", time - data->zero_time, id);
	sem_post(data->messages);
}

void	ft_eating(t_lst *data)
{
	ft_print_message(data, EAT);
	my_usleep(data->eat_time);
	data->last_meal = find_current_time();
}

void	ft_sleeping(t_lst *data)
{
	ft_print_message(data, SLEEP);
	my_usleep(data->sleep_time);
}

void	ft_ph_take_forks(t_lst *data)
{
	sem_wait(data->general);
	sem_wait(data->forks);
	sem_wait(data->forks);
	sem_post(data->general);
}

void	ft_ph_put_forks(t_lst *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
}
