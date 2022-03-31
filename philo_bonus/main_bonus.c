/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:14:46 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/31 13:56:44 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_fill_all_data(t_lst *data)
{
	if (ft_create_semaphores(data) == 1)
		return (1);
	if (ft_allocate_memory(data) == 1)
	{
		ft_cleaning(data);
		return (1);
	}
	ft_define_cycles_numb(data);
	ft_initial_time(data);
	return (0);
}

void	ft_actions(t_lst *data)
{
	while (data->cycles)
	{
		ft_ph_take_forks(data);
		ft_eating(data);
		ft_ph_put_forks(data);
		ft_sleeping(data);
		ft_thinking(data);
		if (data->must_eat != -1)
			data->cycles--;
		if (data->cycles == 0)
			exit(EXIT_SUCCESS);
	}
	exit(EXIT_SUCCESS);
}

void	ft_wait_other_philos(t_lst *data)
{
	long long	time;

	time = find_current_time();
	while (time < data->zero_time + 200)
	{
		usleep(1);
		time = find_current_time();
	}
}

int	ft_create_philos(t_lst *data)
{
	int				n;
	pid_t			pid;

	n = 0;
	ft_initial_time(data);
	while (n < data->numb)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_cleaning(data);
			return (ft_putstr_ret("Error: fork failed\n", 2));
		}
		if (pid == 0)
		{
			data->id = n;
			ft_wait_other_philos(data);
			ft_start_monitoring(data);
			ft_initial_time(data);
			ft_actions(data);
		}
		data->children_pids[n] = pid;
		n++;
	}
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
	if (ft_fill_all_data(&data) == 1)
	{
		return (1);
	}
	if (ft_create_philos(&data) == 1)
	{
		return (1);
	}
	ft_wait_philos(&data);
	ft_cleaning(&data);
	return (0);
}
