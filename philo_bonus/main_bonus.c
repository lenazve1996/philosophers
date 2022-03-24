/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:14:46 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/24 16:39:47 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_initial_time(t_lst *data)
{
	int	n;

	n = 0;
	data->zero_time = find_current_time();
	*data->cur_time = data->zero_time;
	n = 0;
	while (n < data->numb)
	{
		data->last_meal[n++] = data->zero_time;
	}
}

void	ft_close_semaphores(t_lst *data)
{
	sem_close(data->forks);
	sem_close(data->messages);
}

void	ft_cleaning(t_lst *data)
{
	ft_close_semaphores(data);
	if (data->last_meal != NULL)
		free(data->last_meal);
	if (data->cur_time != NULL)
		free(data->cur_time);
	if (data->children_pids != NULL)
		free(data->children_pids);
}

int	ft_create_semaphores(t_lst *data)
{
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->numb);
	if (data->forks == SEM_FAILED)
	{
		perror("");
		return (ft_putstr_ret("Error: sem_open1 failed\n", 2));
	}
	sem_unlink("forks");
	data->messages = sem_open("messages", O_CREAT | O_EXCL, 0644, 1);
	if (data->messages == SEM_FAILED)
	{
		sem_close(data->forks);
		perror("");
		return (ft_putstr_ret("Error: sem_open2 failed\n", 2));
	}
	sem_unlink("messages");
	return (0);
}

int	ft_allocate_memory(t_lst *data)
{
	data->last_meal = (long long *)malloc(sizeof(long long) * data->numb);
	if (data->last_meal == NULL)
	{
		return (ft_putstr_ret("Error: malloc failed\n", 2));
	}
	data->cur_time = (long long *)malloc(sizeof(long long));
	if (data->cur_time == NULL)
	{
		return (ft_putstr_ret("Error: malloc failed\n", 2));
	}
	data->children_pids = (int *)malloc(sizeof(int) * data->numb);
	if (data->children_pids == NULL)
	{
		return (ft_putstr_ret("Error: malloc failed\n", 2));
	}
	return (0);
}

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
	ft_ph_take_forks(data);
	ft_eating(data);
	ft_ph_put_forks(data);
	ft_sleeping(data);
	ft_thinking(data);
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
	return (0);
}

int	ft_create_philos(t_lst *data)
{
	int				n;
	int				cycles;
	pid_t			pid;
	
	n = 0;
	while (n < data->numb)
	{
		pid = fork();
		if (pid == -1)
		{
			return (ft_putstr_ret("Error: fork failed\n", 2));
		}
		if (pid == 0)
		{
			cycles = data->cycles;
			data->id = n;
			ft_create_thread(data);
			while (cycles)
			{
				ft_actions(data);
				if (data->must_eat != -1)
					cycles--;
			}
			exit(EXIT_SUCCESS);
		}
		data->children_pids[n] = pid;
		n++;
	}
	return (0);
}

void	ft_kill_all_philos(t_lst *data)
{		
	int	n;
	
	n = 0;
	while (n < data->numb)
	{
		kill(data->children_pids[n], SIGTERM);
		n++;
	}
}

void	ft_wait_philos(t_lst *data)
{
	int				n;
	int				status;
	
	n = 0;
	while (n < data->numb)
	{
		wait(&status);
		if (status == 768)
		{
			ft_kill_all_philos(data);
			return ;
		}
		n++;
	}
}

static int	ft_creation(t_lst *data)
{
	if (ft_create_philos(data) == 1)
	{
		ft_cleaning(data);
		return (1);
	}
	ft_wait_philos(data);
	ft_cleaning(data);
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
	return (ft_creation(&data));
}
