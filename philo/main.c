/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:14:46 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/25 21:56:17 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_initialize_mutexes(t_lst *data)
{
	int	id;

	id = 0;
	data->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->numb);
	if (data->mut == NULL)
		return (1);
	data->message = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (data->message == NULL)
		return (1);
	printf("data->message %p\n", data->message);
	while (id < data->numb)
	{
		if (pthread_mutex_init(&data->mut[id], NULL) != 0)
		{
			free_mut_array(data, id);
			return (ft_putstr_ret("Error: Mutex init failed\n", 2));
		}
		id++;
	}
	if (pthread_mutex_init(data->message, NULL) != 0)
	{
		return (ft_putstr_ret("Error: Mutex init failed\n", 2));
	}
	return (0);
}

static int	ft_create_threads(t_lst *data)
{
	ft_initial_time(data);
	ft_data_for_philo(data);
	data->already_ate = 0;
	if (ft_run_threads(0, data) == 1)
		return (1);
	usleep(100);
	if (ft_run_threads(1, data) == 1)
		return (1);
	return (0);
}

static int	ft_detach_threads(t_lst *data)
{
	int	id;

	id = 0;
	while (id < data->numb)
	{
		if (pthread_detach(data->philos[id]) != 0)
		{
			return (ft_putstr_ret("Error: pthread_detach failed\n", 2));
		}
		id++;
	}
	return (0);
}

static int	ft_creation(t_lst *data)
{
	data->philos = (pthread_t *)malloc(sizeof(pthread_t) * data->numb);
	if (data->philos == NULL)
		return (1);
	data->ph = (t_ph *)malloc(sizeof(t_ph) * data->numb);
	if (data->ph == NULL)
		return (1);
	if (ft_initialize_mutexes(data) == 1)
		return (1);
	if (ft_create_threads(data) == 1)
		return (1);
	if (ft_detach_threads(data) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_lst	data;

	if (argc != 5 && argc != 6)
	{
		return (ft_putstr_ret("Error\n", 2));
	}
	if (ft_parser(argc, argv, &data) == 1)
	{
		return (ft_putstr_ret("Error\n", 2));
	}
	if (ft_creation(&data) == 1)
	{
		return (ft_clearing(&data, 1));
	}
	ft_monitor_death(&data);
	return (0);
	//else
	//{
	//	return (ft_clearing(&data, 0));
	//}
}
