/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/25 13:23:56 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_actions(void *philosopher)
{
	t_ph				*ph;

	ph = (t_ph *)philosopher;
	while (ph->cycles)
	{
		ft_take_forks(ph);
		ft_eat(ph);
		ft_put_forks(ph);
		if (ph->must_eat != -1)
			ph->cycles--;
		if (ph->cycles == 0)
			return (NULL);
		ft_sleep(ph);
		ft_think(ph);
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
	data->already_ate = 0;
	ft_define_cycles_numb(data);
	while (id < data->numb)
	{
		data->ph[id].id = id;
		data->ph[id].numb = data->numb;
		data->ph[id].message = &data->message;
		data->ph[id].meals = &data->meals;
		data->ph[id].last_dinner = data->zero_time;
		data->ph[id].last_eat_timestamp = data->zero_time;
		data->ph[id].die_time = data->die_time;
		data->ph[id].eat_time = data->eat_time;
		data->ph[id].time = &data->time;
		data->ph[id].already_ate = &data->already_ate;
		data->ph[id].sleep_time = data->sleep_time;
		data->ph[id].must_eat = data->must_eat;
		data->ph[id].cycles = data->cycles;
		data->ph[id].left_fork = &data->mut[id];
		ft_detect_rigth_fork(data, id);
		data->ph[id].zero_time = data->zero_time;
		id++;
	}
}
