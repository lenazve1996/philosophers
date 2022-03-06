/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/06 19:45:47 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_lst data;

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
	data->forks = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]); 
	data->eat_time = ft_atoi(av[3]); 
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else if (ac == 5)
		data->must_eat = 0;
	return (0);
}

void	ft_eat(int i)
{
	if (data.timestamp[i] - data.last_dinner[i] >= data.die_time)
	{
		pthread_mutex_lock(&data.message);
		printf("%lld %d died\n", data.timestamp[i], i + 1);
		pthread_mutex_unlock(&data.message);
		exit(1);
	}
	printf("%lld %d is eating\n", data.timestamp[i], i + 1);
	pthread_mutex_unlock(&data.message);
	usleep(data.eat_time * 1000);
}

void	ft_sleep(int i)
{
	struct timeval		cur_time;
	
	gettimeofday(&cur_time, NULL);
	data.timestamp[i] = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - data.prev_msec[i]; 
	pthread_mutex_lock(&data.message);
	printf("%lld %d is sleeping\n", data.timestamp[i], i + 1);
	pthread_mutex_unlock(&data.message);
	usleep(data.sleep_time * 1000);
}

void	ft_think(int i)
{
	struct timeval		cur_time;
	
	gettimeofday(&cur_time, NULL);
	data.timestamp[i] = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - data.prev_msec[i]; 
	pthread_mutex_lock(&data.message);
	printf("%lld %d is thinking\n", data.timestamp[i], i + 1);
	pthread_mutex_unlock(&data.message);

}
void	*ft_actions(void *i)
{
	int					index;
	int					cycles;
	int					right_fork;
	int					left_fork;
	struct timeval		cur_time;
	
	index = *(int *)i;
	left_fork = index;
	if (index + 1 == data.forks)
		right_fork = 0;
	else 
		right_fork = index + 1;
	if (data.must_eat != 0)
		cycles = data.must_eat;
	else
		cycles = 1;
	while (cycles)
	{
		gettimeofday(&cur_time, NULL);
		if (data.timestamp[index] == 0 && data.prev_msec[index] == 0)
		{
			data.prev_msec[index] = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
		}
		else
		{
			data.timestamp[index] = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - data.prev_msec[index];
			data.prev_msec[index] = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
		}
		pthread_mutex_lock(&data.mut[index]);
		pthread_mutex_lock(&data.mut[index + 1]);
		pthread_mutex_lock(&data.message);
		printf("%lld %d has taken a fork %d\n", data.timestamp[index], index + 1, index);
		printf("%lld %d has taken a fork %d\n", data.timestamp[index], index + 1, index + 1);
		pthread_mutex_unlock(&data.message);
		ft_eat(index);
		pthread_mutex_unlock(&data.mut[index]);
		pthread_mutex_unlock(&data.mut[index + 1]);
		ft_sleep(index);
		if (data.must_eat != 0)
			cycles--;
		ft_think(index);
	}
	return (NULL);
}

int	ft_create_threads()
{
	int	i;

	i = 0;
	data.mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.forks);
	while (i < data.forks)
		pthread_mutex_init(&data.mut[i++], NULL);
	pthread_mutex_init(&data.message, NULL);
	data.philos = (pthread_t *)malloc(sizeof(pthread_t) * data.forks);
	data.timestamp = (long long *)malloc(sizeof(long long) * data.forks);
	data.prev_msec = (long long *)malloc(sizeof(long long) * data.forks);
	data.last_dinner = (long long *)malloc(sizeof(long long) * data.forks);
	data.zero_time = 0;
	i = 0;
	while (i < data.forks)
	{
		data.timestamp[i] = 0;
		data.prev_msec[i] = 0;
		data.last_dinner[i] = 0;
		if (pthread_create(&data.philos[i], NULL, &ft_actions, &i) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data.forks)
	{
		if (pthread_join(data.philos[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data.forks)
		pthread_mutex_destroy(&data.mut[i++]);
	pthread_mutex_init(&data.message, NULL);
	free(data.philos);
	return (0);
}


int	main(int argc, char **argv)
{
	if (argc < 5)
		return (ft_putstr_ret("Error\n", 2));
	if (ft_parser(argc, argv, &data) == 1)
		return (ft_putstr_ret("Error\n", 2));
	printf("%d\n", data.forks);
	printf("%d\n", data.die_time);
	printf("%d\n", data.eat_time);
	printf("%d\n", data.sleep_time);
	printf("%d\n", data.must_eat);
	if (ft_create_threads() == 1)
		return (ft_putstr_ret("Error\n", 2));
}