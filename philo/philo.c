/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/17 19:32:04 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mut_array(t_lst *data, int free_numb)
{
	if (data->mut != NULL)
	{
		while (free_numb != 0)
			pthread_mutex_destroy(&data->mut[--free_numb]);
	}
}

//void	free_thread_array(t_lst *data, int free_numb)
//{
//	int	id;
	
//	id = 0;
//	while (free_numb != 0)
//		pthread_mutex_destroy(&data->mut[--free_numb]);
//	pthread_mutex_destroy(&data->message);
//}

int	ft_clearing(t_lst *data, int error_flag)
{
	if (data->philos != NULL)
		free(data->philos);
	if (data->mut != NULL)
		free(data->mut);
	if (data->ph != NULL)
		free(data->ph);
	free_mut_array(data, data->numb);
	return (error_flag);
}

static int	ft_check_characters(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit_orsign(str[i]) == 0)
			return (1);
		if (i == 0 && str[i + 1] == '\0' && (str[i] == '+' || str[i] == '-'))
			return (1);
		if (i == 0 && (str[i + 1] == '+' || str[i + 1] == '-') && \
		(str[i] == '+' || str[i] == '-'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_putstr_ret(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	return (1);
}

int	ft_parser(int ac, char **av, t_lst *data)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_check_characters(av[i]) == 1)
			return (1);
		i++;
	}
	data->numb = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]); 
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else if (ac == 5)
		data->must_eat = 0;
	if (data->numb <= 0 || data->die_time < 0 || data->eat_time < 0 \
	|| data->sleep_time < 0 || data->must_eat < 0)
		return (1);
	return (0);
}

void	my_usleep(long long msec)
{
	struct timeval				cur_time;
	unsigned long long 			start_time;
	unsigned long long 			end_time;
	unsigned long long 			comparison;
	
	end_time = 0;
	gettimeofday(&cur_time, NULL);
	start_time = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
	comparison = start_time + msec;
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

void	ft_eat(t_ph *ph)
{
	pthread_mutex_lock(ph->message);
	printf("%lld %d is eating\n", *ph->time - ph->zero_time, ph->id + 1);
	pthread_mutex_unlock(ph->message);
	//ph->last_dinner = *ph->time + 200;
	//usleep(ph->eat_time * 1000);
	my_usleep(ph->eat_time);
	ph->last_eat_timestamp = *ph->time;
	ph->last = *ph->time - ph->last_time;
	ph->last_time = *ph->time;
	pthread_mutex_lock(ph->message);
	ph->already_ate++;
	pthread_mutex_unlock(ph->message);
	//printf("ph->last %lld\n", ph->last);
	//printf("ph->last_time %lld\n", ph->last_time);
	//printf("ph->time %lld\n", *ph->time);
	//printf("--->>>>> %lld\n", *ph->time - ph->last_eat_timestamp);
	//ph->last_dinner = *ph->time;
}

void	ft_sleep(t_ph *ph)
{
	pthread_mutex_lock(ph->message);
	printf("%lld %d is sleeping\n", *ph->time - ph->zero_time, ph->id + 1);
	pthread_mutex_unlock(ph->message);
	//usleep(ph->sleep_time * 1000);
	my_usleep(ph->sleep_time);
}

void	ft_think(t_ph *ph)
{
	pthread_mutex_lock(ph->message);
	printf("%lld %d is thinking\n", *ph->time - ph->zero_time, ph->id + 1);
	pthread_mutex_unlock(ph->message);
}

void	*ft_actions(void *philosopher)
{
	t_ph				*ph;
	int					cycles;
	
	ph = (t_ph *)philosopher;
	if (ph->must_eat != 0)
		cycles = ph->must_eat;
	else
		cycles = 1;
	while (cycles)
	{
		//if (ph->id + 1 != ph->numb)
		//	pthread_mutex_lock(ph->left_fork);
		//else if (ph->id + 1 == ph->numb)
		//	pthread_mutex_lock(ph->right_fork);
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->message);
		printf("%lld %d has taken a fork\n", *ph->time - ph->zero_time, ph->id + 1);
		pthread_mutex_unlock(ph->message);
		pthread_mutex_lock(ph->right_fork);
		//if (ph->id + 1 != ph->numb)
		//	pthread_mutex_lock(ph->right_fork);
		//else if (ph->id + 1 == ph->numb)
		//	pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->message);
		if (ph->id + 1 != ph->numb)
			printf("%lld %d has taken a fork\n", *ph->time - ph->zero_time, ph->id + 1);
		else if (ph->id + 1 == ph->numb)
			printf("%lld %d has taken a fork\n", *ph->time - ph->zero_time, ph->id + 1);
		pthread_mutex_unlock(ph->message);
		ft_eat(ph);
		//if (ph->id + 1 != ph->numb)
		//{
		//	pthread_mutex_unlock(ph->right_fork);
		//	usleep(100);
		//	pthread_mutex_unlock(ph->left_fork);
		//	usleep(200);
		//}
		//else if (ph->id + 1 == ph->numb)
		//{
		//	pthread_mutex_unlock(ph->left_fork);
		//	usleep(100);
		//	pthread_mutex_unlock(ph->right_fork);
		//	usleep(200);
		//}
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		ft_sleep(ph);
		ft_think(ph);
		if (ph->must_eat != 0)
			cycles--;
			
	}
	return (NULL);
}

int	ft_run_threads(int id, t_lst *data)
{
	int	rv;
	
	while (id < data->numb)
	{
		rv = pthread_create(&data->philos[id], NULL, &ft_actions, &data->ph[id]);
		if (rv != 0)
		{
			printf("Error: return code from pthread_create is %d", rv);
			return (1);
		}
		id = id + 2;
	}
	return (0);
}

int	ft_creation(t_lst *data)
{
	int					id;
	struct timeval		cur_time;
	
	id = 0;
	gettimeofday(&cur_time, NULL);
	data->zero_time = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
	data->time = data->zero_time;
	data->already_ate = 0;
	while (id < data->numb)
	{
		data->ph[id].id = id;
		data->ph[id].numb = data->numb;
		data->ph[id].message = &data->message;
		data->ph[id].last_dinner = data->zero_time;
		data->ph[id].last = 0;
		data->ph[id].last_time = data->zero_time;
		data->ph[id].last_eat_timestamp = data->zero_time;
		data->ph[id].die_time = data->die_time;
		data->ph[id].eat_time = data->eat_time;
		data->ph[id].time = &data->time;
		data->ph[id].already_ate = &data->already_ate; 
		data->ph[id].sleep_time = data->sleep_time;
		data->ph[id].must_eat = data->must_eat;
		data->ph[id].already_ate = 0;
		data->ph[id].left_fork = &data->mut[id];
		if (id + 1 != data->numb)
			data->ph[id].right_fork = &data->mut[id + 1];
		else if (id + 1 == data->numb)
			data->ph[id].right_fork = &data->mut[0];
		data->ph[id].zero_time = data->zero_time;
		id++;
	}
	if (ft_run_threads(0, data) == 1)
		return (2);
	usleep(100);
	if (ft_run_threads(1, data) == 1)
		return (1);
	return (0);

	
}

int	ft_initialize_mutexes(t_lst *data)
{
	int				id;

	id = 0;
	while (id < data->numb)
	{
		if (pthread_mutex_init(&data->mut[id], NULL) != 0)
		{
			free_mut_array(data, id);
			return (1);
		}
		id++;
	}
	if (pthread_mutex_init(&data->message, NULL) != 0)
	{
		pthread_mutex_destroy(&data->message);
		free_mut_array(data, id);
		return (1);
	}
	//if (pthread_mutex_init(&data->new, NULL) != 0)
	//{
	//	pthread_mutex_destroy(&data->new);
	//	pthread_mutex_destroy(&data->message);
	//	free_mut_array(data, id);
	//	return (1);
	//}
	return (0);
}

void	ft_monitor_death(t_lst *data)
{
	struct timeval		cur_time;
	long long 			timestamp;
	int					i;
	int					times_to_eat;
	
	times_to_eat = data->numb * data->must_eat;
	while (1)
	{
		i = 0;
		while (i < data->numb)
		{
		gettimeofday(&cur_time, NULL);
		timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
		data->time = timestamp;
		//data->time = timestamp - data->zero_time;
		//printf("timestamp %lld\n", timestamp);
		//printf("data->time %lld\n", data->time);
			//printf("data->ph[i].last_dinner %lld\n", data->ph[i].last_dinner);
			//printf("data->die_time %d\n", data->die_time);
			//if (data->time - data->ph[i].last_dinner > data->die_time || ((data->die_time < data->eat_time) && (timestamp - data->zero_time == data->die_time)))
			//{
			//	pthread_mutex_lock(&data->message);
			//	printf("\nphilo %d time died %lld\n", data->ph->id + 1, data->time - data->ph[i].last_dinner); //del
			//	printf("%lld %d died\n", timestamp - data->zero_time, data->ph->id + 1);
			//	pthread_mutex_unlock(&data->message);
			//	return ;
			//}
			if (data->must_eat != 0 && data->already_ate == times_to_eat)
			{
				exit(0);
			}
			if (data->ph[i].last > data->die_time || data->time - data->ph[i].last_eat_timestamp > data->die_time)
			{
				pthread_mutex_lock(&data->message);
				printf("\nphilo %d time died %lld\n", data->ph[i].id + 1, data->time - data->ph[i].last_eat_timestamp); //del
				printf("%lld %d died\n", timestamp - data->zero_time, data->ph[i].id + 1);
				pthread_mutex_unlock(&data->message);
				return ;
			}
			i++;
		}
	}
}

int	ft_create_threads(t_lst *data)
{
	int	id;

	data->philos = (pthread_t *)malloc(sizeof(pthread_t) * data->numb);
	if (data->philos == NULL)
		return(1);
	data->ph = (t_ph *)malloc(sizeof(t_ph) * data->numb);
	if (data->ph == NULL)
		return(1);
	data->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->numb);
	if (data->mut == NULL)
		return(1);
	ft_initialize_mutexes(data);
	if (ft_creation(data) == 1)
		return (1);
	id = 0;
	while (id < data->numb)
	{
		if (pthread_detach(data->philos[id]) != 0)
			return (1);
		id++;
	}
	ft_monitor_death(data);
	free_mut_array(data, id);
	free(data->philos);
	return (0);
}


int	main(int argc, char **argv)
{
	t_lst	data;
	
	if (argc < 5)
		return (ft_putstr_ret("Error\n", 2));
	if (ft_parser(argc, argv, &data) == 1)
		return (ft_putstr_ret("Error\n", 2));
	//printf("%d\n", data.numb);
	//printf("%d\n", data.die_time);
	//printf("%d\n", data.eat_time);
	//printf("%d\n", data.sleep_time);
	//printf("%d\n", data.must_eat);
	if (ft_create_threads(&data) == 1)
	{
		ft_clearing(&data, 1);
		return (ft_putstr_ret("Error\n", 2));
	}
	//else
	//	ft_clearing(&data, 0);
}