/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:14:46 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/05/01 19:08:43 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutex_array(pthread_mutex_t **mutex, int mutex_numb, t_lst *data)
{
	int	id;
	
	id = 0;
	*mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * mutex_numb);
	if (*mutex == NULL)
		return (MUT_CREATE_ERROR);
	while (id < mutex_numb)
	{
		if (pthread_mutex_init(&(*mutex)[id], NULL) != 0)
		{
			free_mut_array(data, id);
			ft_putstr_ret("Error: Create mutex failed\n", 2);
			return (MUT_CREATE_ERROR);
		}
		id++;
	}
	return (0);
}

int create_mutex(pthread_mutex_t **mutex)
{
	*mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
		return (MUT_CREATE_ERROR);
	if (pthread_mutex_init(*mutex, NULL) != 0)
	{
		ft_putstr_ret("Error: Mutex init failed\n", 2);
		return (MUT_CREATE_ERROR);
	}
	return (0);
}

static int	initialize_mutexes(t_lst *data)
{
	int	id;

	id = 0;
	if (create_mutex_array(&data->mut, data->numb, data) == MUT_CREATE_ERROR)
		return (MUT_CREATE_ERROR);
	if (create_mutex(&data->message) == MUT_CREATE_ERROR)
		return (MUT_CREATE_ERROR);
	return (0);
}

static int	ft_create_threads(t_lst *data)
{
	data->already_ate = 0;
	if (ft_run_threads(0, data) == 1)
		return (1);
	usleep(100);
	if (ft_run_threads(1, data) == 1)
		return (1);
	return (0);
}

static int	ft_creation(t_lst *data)
{
	data->philos = (pthread_t *)malloc(sizeof(pthread_t) * data->numb);
	if (data->philos == NULL)
		return (MALLOC_ERROR);
	data->philo_specs = (t_ph *)malloc(sizeof(t_ph) * data->numb);
	if (data->philo_specs == NULL)
		return (MALLOC_ERROR);
	if (initialize_mutexes(data) == MUT_CREATE_ERROR)
		return (MUT_CREATE_ERROR);
	ft_initial_time(data);
	set_philo_specs(data);
	if (ft_create_threads(data) == 1)
		return (1);
	ft_monitoring(data);
	ft_wait_threads(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_lst	data;

	data = (t_lst){};
	if (argc != 5 && argc != 6)
	{
		return (ft_putstr_ret("Error\n", 2));
	}
	if (parser(argc, argv, &data) == PARSER_ERROR)
	{
		return (ft_putstr_ret("Error\n", 2));
	}
	if (ft_creation(&data) == 1)
	{
		return (ft_clearing(&data, 1));
	}
	return (ft_clearing(&data, 0));
}
