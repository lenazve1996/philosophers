/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/09 19:41:25 by ayajirob@st      ###   ########.fr       */
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
	return (0);
}

void	ft_eat(t_ph *ph, long long timestamp)
{
	if (timestamp - ph->last_dinner > ph->die_time)
	{
		pthread_mutex_lock(ph->message);
		printf("%lld %d died\n", timestamp, ph->id + 1);
		pthread_mutex_unlock(ph->message);
		exit(1);
	}
	pthread_mutex_lock(ph->message);
	printf("%lld %d is eating\n", timestamp, ph->id + 1);
	pthread_mutex_unlock(ph->message);
	ph->last_dinner = timestamp;
	usleep(ph->eat_time * 1000);
}

void	ft_sleep(t_ph *ph)
{
	struct timeval		cur_time;
	long long			timestamp;
	
	gettimeofday(&cur_time, NULL);
	timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - ph->zero_time; 
	pthread_mutex_lock(ph->message);
	printf("%lld %d is sleeping\n", timestamp, ph->id + 1);
	pthread_mutex_unlock(ph->message);
	usleep(ph->sleep_time * 1000);
}

void	ft_think(t_ph *ph)
{
	struct timeval		cur_time;
	long long			timestamp;
	
	gettimeofday(&cur_time, NULL);
	timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - ph->zero_time;
	pthread_mutex_lock(ph->message);
	printf("%lld %d is thinking\n", timestamp, ph->id + 1);
	pthread_mutex_unlock(ph->message);
}
void	*ft_actions(void *philosopher)
{
	t_ph				*ph;
	long long			timestamp;
	int					cycles;
	struct timeval		cur_time;
	
	ph = (t_ph *)philosopher;
	if (ph->must_eat != 0)
		cycles = ph->must_eat;
	else
		cycles = 1;
	while (cycles)
	{
		gettimeofday(&cur_time, NULL);
		if (ph->zero_time == -1)
		{
			ph->zero_time = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
			timestamp = 0;
		}
		else
			timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - ph->zero_time;
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		pthread_mutex_lock(ph->message);
		printf("%lld %d has taken a fork %d\n", timestamp, ph->id + 1, ph->id);
		if (ph->id != ph->numb)
			printf("%lld %d has taken a fork %d\n", timestamp, ph->id + 1, ph->id + 1);
		else if (ph->id == ph->numb)
			printf("%lld %d has taken a fork %d\n", timestamp, ph->id + 1, 0);
		pthread_mutex_unlock(ph->message);
		ft_eat(ph, timestamp);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		ft_sleep(ph);
		if (ph->must_eat != 0)
			cycles--;
		ft_think(ph);
	}
	return (NULL);
}

int	ft_creation(t_lst *data, pthread_mutex_t message)
{
	int	id;
	
	id = 0;
	while (id < data->numb)
	{
		data->ph[id].id = id;
		data->ph[id].numb = data->numb;
		data->ph[id].message = &message;
		data->ph[id].last_dinner = 0;
		data->ph[id].die_time = data->die_time;
		data->ph[id].eat_time = data->eat_time;
		data->ph[id].sleep_time = data->sleep_time;
		data->ph[id].must_eat = data->must_eat;
		data->ph[id].left_fork = &data->mut[id];
		if (id != data->numb)
			data->ph[id].right_fork = &data->mut[id + 1];
		else if (id == data->numb)
			data->ph[id].right_fork = &data->mut[0];
		data->ph[id].zero_time = -1;
		if (pthread_create(&data->philos[id], NULL, &ft_actions, &data->ph[id]) != 0)
		{
			//free_thread_array(data, id);
			return (1);
		}
		id++;
	}
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
		return (1);
	}
	return (0);
}

int	ft_create_threads(t_lst *data)
{
	int	id;

	printf("%p\n", data->philos);
	printf("%p\n", data->ph);
	printf("%p\n", data->mut);
	data->philos = (pthread_t *)malloc(sizeof(pthread_t) * data->numb);
	if (data->philos == NULL)
		return(1);
	data->ph = (t_ph *)malloc(sizeof(t_ph) * data->numb);
	if (data->ph == NULL)
	{
		return(1);
	}
	data->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->numb);
	if (data->mut == NULL)
	{
		return(1);
	}
	ft_initialize_mutexes(data);
	if (ft_creation(data, data->message) == 1)
	{
		return (1);
	}
	id = 0;
	while (id < data->numb)
	{
		if (pthread_join(data->philos[id], NULL) != 0)
			return (1);
		id++;
	}
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
	printf("%d\n", data.numb);
	printf("%d\n", data.die_time);
	printf("%d\n", data.eat_time);
	printf("%d\n", data.sleep_time);
	printf("%d\n", data.must_eat);
	if (ft_create_threads(&data) == 1)
	{
		//ft_clearing(&data, 1);
		return (ft_putstr_ret("Error\n", 2));
	}
	//else
	//	ft_clearing(&data, 0);
}