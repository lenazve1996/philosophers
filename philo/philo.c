/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/07 19:05:37 by ayajirob@st      ###   ########.fr       */
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

void	ft_eat(t_ph *ph, long long timestamp)
{
	if (timestamp - ph->last_dinner == ph->die_time)
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

void	ft_sleep(int i)
{
	struct timeval		cur_time;
	
	gettimeofday(&cur_time, NULL);
	data.timestamp[i] = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - data.prev_msec[i]; 
	pthread_mutex_lock(ph->message);
	printf("%lld %d is sleeping\n", data.timestamp[i], i + 1);
	pthread_mutex_unlock(ph->message);
	usleep(data.sleep_time * 1000);
}

void	ft_think(int i)
{
	struct timeval		cur_time;
	
	gettimeofday(&cur_time, NULL);
	data.timestamp[i] = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - data.prev_msec[i]; 
	pthread_mutex_lock(ph->message);
	printf("%lld %d is thinking\n", data.timestamp[i], i + 1);
	pthread_mutex_unlock(ph->message);

}
void	*ft_actions(void *philosopher)
{
	t_ph				*ph;
	int					index;
	long long			timestamp;
	int					cycles;
	int					right_fork;
	int					left_fork;
	struct timeval		cur_time;
	
	//left_fork = index;
	//if (index + 1 == data.forks)
	//	right_fork = 0;
	//else 
	//	right_fork = index + 1;
	ph = (t_ph *)philosopher;
	if (ph->must_eat != 0)
		cycles = ph->must_eat;
	else
		cycles = 1;
	while (cycles)
	{
		gettimeofday(&cur_time, NULL);
		//printf("HERE\n");
		if (cycles == 1)
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
		if (ph->id != data.forks)
			printf("%lld %d has taken a fork %d\n", data.timestamp[index], ph->id + 1, ph->id + 1);
		else if (ph->id == data.forks)
			printf("%lld %d has taken a fork %d\n", data.timestamp[index], ph->id + 1, 0);
		pthread_mutex_unlock(ph->message);
		ft_eat(ph, timestamp);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
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
	//pthread_mutex_t *message;

	i = 0;
	data.mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.forks);
	while (i < data.forks)
		pthread_mutex_init(&data.mut[i++], NULL);
	//pthread_mutex_init(message, NULL);
	pthread_mutex_init(&data.message, NULL);
	data.philos = (pthread_t *)malloc(sizeof(pthread_t) * data.forks);
	data.timestamp = (long long *)malloc(sizeof(long long) * data.forks);
	data.prev_msec = (long long *)malloc(sizeof(long long) * data.forks);
	data.last_dinner = (long long *)malloc(sizeof(long long) * data.forks);
	data.ph = (t_ph *)malloc(sizeof(t_ph) * data.forks);
	//data.zero_time = 0;
	i = 0;
	while (i < data.forks)
	{
		data.ph[i].id = i;
		//data.ph[i].message = message;
		//data.ph[i].zero_msec = 0;
		data.ph[i].last_dinner = 0;
		data.ph[i].die_time = data.die_time;
		data.ph[i].eat_time = data.eat_time;
		data.ph[i].sleep_time = data.sleep_time;
		data.ph[i].must_eat = data.must_eat;
		data.ph[i].left_fork = &data.mut[i];
		if (i != data.forks)
			data.ph[i].right_fork = &data.mut[i + 1];
		else if (i == data.forks)
			data.ph[i].right_fork = &data.mut[0];
		data.timestamp[i] = 0;
		data.prev_msec[i] = 0;
		data.last_dinner[i] = 0;
		if (pthread_create(&data.philos[i], NULL, &ft_actions, &data.ph[i]) != 0)
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