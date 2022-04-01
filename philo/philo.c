/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/04/01 13:16:24 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_message(t_lst *data, t_ph *ph, int action)
{
	int	id;

	id = ph->id + 1;
	if (ft_scan_death(data) == 1)
		return (1);
	pthread_mutex_lock(data->message);
	if (action == TAKE_FORK)
		printf("%lld %d has taken a fork\n", data->time - data->zero_time, id);
	else if (action == EAT)
		printf("%lld %d is eating\n", data->time - data->zero_time, id);
	else if (action == SLEEP)
		printf("%lld %d is sleeping\n", data->time - data->zero_time, id);
	else if (action == THINK)
		printf("%lld %d is thinking\n", data->time - data->zero_time, id);
	pthread_mutex_unlock(data->message);
	return (0);
}

static void	*ft_actions(void *philosopher)
{
	t_ph				*ph;
	t_lst				*data;

	ph = (t_ph *)philosopher;
	data = (t_lst *)ph->main_data;
	while (ph->cycles)
	{
		if (ft_take_forks(ph, data) == 1)
			return (NULL);
		if (ft_eat(ph, data) == 1)
			return (NULL);
		ft_put_forks(ph);
		if (data->must_eat != -1)
			ph->cycles--;
		if (ph->cycles == 0)
			return (NULL);
		if (ft_sleep(ph, data) == 1)
			return (NULL);
		if (ft_think(ph, data) == 1)
			return (NULL);
	}
	return (NULL);
}

int	ft_run_threads(int id, t_lst *data)
{
	int	r;

	while (id < data->numb)
	{
		r = pthread_create(&data->philos[id], NULL, &ft_actions, &data->ph[id]);
		if (r != 0)
		{
			ft_putstr_ret("pthread_create failed\n", 2);
			return (1);
		}
		id = id + 2;
	}
	return (0);
}

static void	ft_detect_rigth_fork(t_lst *data, int id)
{
	if (id + 1 != data->numb)
		data->ph[id].right_fork = &data->mut[id + 1];
	else if (id + 1 == data->numb)
		data->ph[id].right_fork = &data->mut[0];
}

void	ft_data_for_philo(t_lst *data)
{
	int	id;

	id = 0;
	ft_define_cycles_numb(data);
	while (id < data->numb)
	{
		data->ph[id].id = id;
		data->ph[id].last_dinner = data->zero_time;
		data->ph[id].main_data = data;
		data->ph[id].cycles = data->cycles;
		data->ph[id].left_fork = &data->mut[id];
		ft_detect_rigth_fork(data, id);
		id++;
	}
}
