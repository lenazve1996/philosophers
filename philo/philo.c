/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/02/22 19:13:45 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex[3];
pthread_mutex_t sleeping;
pthread_mutex_t eat;
pthread_mutex_t forks;
pthread_mutex_t t;
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
	struct timeval	cur_time;
	long int		timestamp;
	
	pthread_mutex_lock(&t);
	gettimeofday(&cur_time, NULL);
	timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec - data.msec;
	data.msec = cur_time.tv_sec * 1000 + cur_time.tv_usec;
	pthread_mutex_unlock(&t);
	pthread_mutex_lock(&eat);
	printf("%ld %d is eating\n", timestamp, i);
	pthread_mutex_unlock(&eat);
	usleep(data.eat_time);
	return ;
}

void	ft_take_fork(int i)
{
	struct timeval	cur_time;
	long int		timestamp;
	
	pthread_mutex_lock(&t);
	gettimeofday(&cur_time, NULL);
	timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec - data.msec;
	data.msec = cur_time.tv_sec * 1000 + cur_time.tv_usec;
	pthread_mutex_unlock(&t);
	pthread_mutex_lock(&forks);
	printf("%ld %d has taken a fork %d\n", timestamp, i, i);
	printf("%ld %d has taken a fork %d\n", timestamp, i, i+1);
	pthread_mutex_unlock(&forks);
	ft_eat(i);
	return ;
}

void	ft_sleep(int i)
{
	struct timeval	cur_time;
	long int		timestamp;
	
	pthread_mutex_lock(&t);
	timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec - data.msec;
	data.msec = cur_time.tv_sec * 1000 + cur_time.tv_usec;
	pthread_mutex_unlock(&t);
	gettimeofday(&cur_time, NULL);
	pthread_mutex_lock(&sleeping);
	printf("%ld %d is sleeping\n", timestamp, i);
	pthread_mutex_unlock(&sleeping);
	usleep(data.sleep_time);
	return ;
}
void	*ft_actions(void *i)
{
	int index;

	index = *(int *)i;
	pthread_mutex_lock(&mutex[index]);
	pthread_mutex_lock(&mutex[index + 1]);
	ft_take_fork(*(int *)i + 1);
	pthread_mutex_unlock(&mutex[index]);
	pthread_mutex_unlock(&mutex[index + 1]);
	ft_sleep(*(int *)i + 1);
	return (NULL);
}

int	ft_create_threads(t_lst *data)
{
	int i;

	i = 0;
	while (i < data->forks)
		pthread_mutex_init(&mutex[i++], NULL);
	pthread_mutex_init(&eat, NULL);
	pthread_mutex_init(&sleeping, NULL);
	pthread_mutex_init(&forks, NULL);
	data->philos = (pthread_t *)malloc(sizeof(pthread_t) * data->forks);
	i = 0;
	while (i < data->forks)
	{
		if (pthread_create(&data->philos[i], NULL, &ft_actions, &i) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->forks)
	{
		if (pthread_join(data->philos[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->forks)
		pthread_mutex_destroy(&mutex[i++]);
	pthread_mutex_destroy(&eat);
	pthread_mutex_destroy(&sleeping);
	pthread_mutex_destroy(&forks);
	free(data->philos);
	return (0);
}


int	main(int argc, char **argv)
{
	struct timeval cur_time;
	
	if (argc < 5)
		return (ft_putstr_ret("Error\n", 2));
	if (ft_parser(argc, argv, &data) == 1)
		return (ft_putstr_ret("Error\n", 2));
	gettimeofday(&cur_time, NULL);
	data.msec = cur_time.tv_sec * 1000 + cur_time.tv_usec;
	printf("seconds : %ld microseconds : %d\n", cur_time.tv_sec, cur_time.tv_usec);
	printf("%lld\n", data.msec);
	printf("%d\n", data.forks);
	printf("%d\n", data.die_time);
	printf("%d\n", data.eat_time);
	printf("%d\n", data.sleep_time);
	printf("%d\n", data.must_eat);
	if (ft_create_threads(&data) == 1)
		return (ft_putstr_ret("Error\n", 2));
}