/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:14:46 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/21 19:37:05 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//static int	ft_initialize_mutexes(t_lst *data)
//{
//	int	id;

//	id = 0;
//	data->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->numb);
//	if (data->mut == NULL)
//		return (1);
//	while (id < data->numb)
//	{
//		if (pthread_mutex_init(&data->mut[id], NULL) != 0)
//		{
//			free_mut_array(data, id);
//			return (ft_putstr_ret("Error: Mutex init failed\n", 2));
//		}
//		id++;
//	}
//	if (pthread_mutex_init(&data->message, NULL) != 0)
//	{
//		free_mut_array(data, id);
//		return (ft_putstr_ret("Error: Mutex init failed\n", 2));
//	}
//	return (0);
//}

//static int	ft_create_threads(t_lst *data)
//{
//	ft_initial_time(data);
//	ft_data_for_philo(data);
//	data->already_ate = 0;
//	if (ft_run_threads(0, data) == 1)
//		return (1);
//	usleep(100);
//	if (ft_run_threads(1, data) == 1)
//		return (1);
//	return (0);
//}

//static int	ft_detach_threads(t_lst *data)
//{
//	int	id;

//	id = 0;
//	while (id < data->numb)
//	{
//		if (pthread_detach(data->philos[id]) != 0)
//		{
//			return (ft_putstr_ret("Error: pthread_detach failed\n", 2));
//		}
//		id++;
//	}
//	return (0);
//}

static int	ft_creation(t_lst *data)
{
	int				n;
	//pthread_t		thread;
	sem_t			*semaphore;
	sem_t			*message;
	int				status;
	long long		*ph;
	//int				r;
	pid_t			pid;
	
	//n = 0;
	//semaphore = malloc(data->numb * (sem_t *))
	//while (n < data->numb)
	//{
	//	semaphore[n] = sem_open(name, O_CREAT);
	//	n++;
	//}
	ph = (long long *)malloc(sizeof(long long) * data->numb);
	semaphore = sem_open("semaphore", O_CREAT | O_EXCL, 0644, 1);
	if (semaphore == SEM_FAILED)
	{
		perror("");
		return (ft_putstr_ret("Error: sem_open1 failed\n", 2));
	}
	sem_unlink("semaphore");
	message = sem_open("message", O_CREAT | O_EXCL, 0644, 1);
	if (message == SEM_FAILED)
	{
		perror("");
		return (ft_putstr_ret("Error: sem_open2 failed\n", 2));
	}
	sem_unlink("message");
	n = 0;
	ft_initial_time(data);
	while (n < data->numb)
	{
		pid = fork();
		if (pid == -1)
		{
			sem_unlink("semaphore");
			sem_close(semaphore);
			return (ft_putstr_ret("Error: fork failed\n", 2));
		}
		if (pid == 0)
		{
			int	k;
			int	cycles;

			k = 0;
			ft_define_cycles_numb(data);
			cycles = data->cycles;
			while (cycles)
			{
				sem_wait(semaphore);
				printf("Child here\n");
				sleep(1);
				ft_ph_take_forks(data, n, message);
				ft_eating(data, n, message, ph);
				//ft_ph_put_forks(data, n, message);
				sem_post(semaphore);
				ft_sleeping(data, n, message);
				ft_thinking(data, n, message);
				if (data->must_eat != -1)
					cycles--;
			}
			exit(EXIT_SUCCESS);
		}
		n++;
	}
	//r = pthread_create(&thread, NULL, &ft_monitoring, &data);
	//	if (r != 0)
	//	{
	//		ft_putstr_ret("pthread_create failed\n", 2);
	//		return (1);
	//	}
	n = 0;
	while (n < data->numb)
	{
		wait(&status);
		n++;
	}
	sem_close(semaphore);
	sem_close(message);
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
	printf("data->numb %d\n", data.numb);
	ft_creation(&data);
	//{
	//	return (ft_clearing(&data, 1)); 
	//}
	//else
	//{
	//	return (ft_clearing(&data, 0));
	//}
	return (0);
}
