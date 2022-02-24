/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/02/24 19:39:18 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex[3];
pthread_mutex_t take_forks;
pthread_mutex_t message;
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
	struct timeval		cur_time;
	unsigned long long	timestamp;
	
	gettimeofday(&cur_time, NULL);
	timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec - data.start_msec; 
	pthread_mutex_lock(&message);
	printf("%llu %d is eating\n", timestamp, i + 1);
	pthread_mutex_unlock(&message);
	usleep(data.eat_time);
}

void	ft_sleep(int i)
{
	struct timeval		cur_time;
	unsigned long long	timestamp;
	
	gettimeofday(&cur_time, NULL);
	timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec - data.start_msec; 
	pthread_mutex_lock(&message);
	printf("%llu %d is sleeping\n", timestamp, i + 1);
	pthread_mutex_unlock(&message);
	usleep(data.sleep_time);

}
void	*ft_actions(void *i)
{
	int					index;
	int					right_fork;
	int					left_fork;
	unsigned long long	timestamp;
	struct timeval		cur_time;
	
	index = *(int *)i;
	timestamp = 0;
	left_fork = index;
	if (index + 1 == data.forks)
		right_fork = 0;
	else 
		right_fork = index + 1;
	printf("here index %d\n", index);
	pthread_mutex_lock(&take_forks);
	pthread_mutex_lock(&mutex[index]);
	pthread_mutex_lock(&mutex[index + 1]);
	pthread_mutex_unlock(&take_forks);
	//if (index == 0)
	//	timestamp = 0;
	//else
	//{
	gettimeofday(&cur_time, NULL);
	timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec - data.start_msec;
	//}
	pthread_mutex_lock(&message);
	printf("%llu %d has taken a fork %d\n", timestamp, index + 1, index);
	printf("%llu %d has taken a fork %d\n", timestamp, index + 1, index + 1);
	printf("seconds : %ld microseconds : %d together: %ld\n", cur_time.tv_sec, cur_time.tv_usec, cur_time.tv_sec * 1000 + cur_time.tv_usec);
	pthread_mutex_unlock(&message);
	ft_eat(index);
	pthread_mutex_unlock(&mutex[index]);
	pthread_mutex_unlock(&mutex[index + 1]);
	ft_sleep(index);
	return (NULL);
}

int	ft_create_threads()
{
	int				i;
	struct timeval	cur_time;

	i = 0;
	while (i < data.forks)
		pthread_mutex_init(&mutex[i++], NULL);
	pthread_mutex_init(&message, NULL);
	pthread_mutex_init(&take_forks, NULL);
	gettimeofday(&cur_time, NULL);
	data.start_msec = cur_time.tv_sec * 1000 + cur_time.tv_usec;
	printf("seconds : %ld microseconds : %d together: %lld\n", cur_time.tv_sec, cur_time.tv_usec, data.start_msec);
	data.philos = (pthread_t *)malloc(sizeof(pthread_t) * data.forks);
	i = 0;
	while (i < data.forks)
	{
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
		pthread_mutex_destroy(&mutex[i++]);
	pthread_mutex_destroy(&take_forks);
	pthread_mutex_init(&message, NULL);
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