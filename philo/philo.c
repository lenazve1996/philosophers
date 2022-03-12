/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/12 19:42:52 by ayajirob@st      ###   ########.fr       */
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

void	my_usleep(long long microseconds)
{
	struct timeval				cur_time;
	unsigned long long 			start_time;
	unsigned long long 			end_time;
	
	end_time = 0;
	gettimeofday(&cur_time, NULL);
	start_time = cur_time.tv_sec * 1000000 + cur_time.tv_usec;
	while (1)
	{
		gettimeofday(&cur_time, NULL);
		end_time = cur_time.tv_sec * 1000000 + cur_time.tv_usec;
		if (end_time == start_time + microseconds)
		{
			return ;
		}
	}
}

void	ft_eat(t_ph *ph, int first_cycle_flag)
{
	struct timeval		cur_time;
	long long 			time;
	
	gettimeofday(&cur_time, NULL);
	time = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
	ph->timestamp = time - ph->zero_time;
	if (first_cycle_flag)
		ph->last_dinner = time - ph->eat_time;
	else
		ph->last_dinner = time;
	pthread_mutex_lock(ph->message);
	printf("%lld %d is eating\n", ph->timestamp, ph->id + 1);
	pthread_mutex_unlock(ph->message);
	usleep(ph->eat_time * 1000);
	//my_usleep(ph->eat_time * 1000);
}

void	ft_sleep(t_ph *ph)
{
	struct timeval		cur_time;
	
	gettimeofday(&cur_time, NULL);
	ph->timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - ph->zero_time; 
	pthread_mutex_lock(ph->message);
	printf("%lld %d is sleeping\n", ph->timestamp, ph->id + 1);
	pthread_mutex_unlock(ph->message);
	usleep(ph->sleep_time * 1000);
	//my_usleep(ph->sleep_time * 1000);
}

void	ft_think(t_ph *ph)
{
	struct timeval		cur_time;
	
	gettimeofday(&cur_time, NULL);
	ph->timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - ph->zero_time;
	pthread_mutex_lock(ph->message);
	printf("%lld %d is thinking\n", ph->timestamp, ph->id + 1);
	pthread_mutex_unlock(ph->message);
}
void	*ft_actions(void *philosopher)
{
	t_ph				*ph;
	int					first_cycle_flag;
	int					cycles;
	struct timeval		cur_time;
	
	ph = (t_ph *)philosopher;
	if (ph->must_eat != 0)
		cycles = ph->must_eat;
	else
		cycles = 1;
	first_cycle_flag = 1;
	while (cycles)
	{
		//printf("%p\n", ph->left_fork);
		//printf("%p\n", ph->right_fork);
		
		pthread_mutex_lock(ph->new);
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->message);
		gettimeofday(&cur_time, NULL);
		ph->timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - ph->zero_time;
		//printf("ph->timestamp: %lld\n", ph->timestamp);
		printf("%lld %d has taken a fork %d\n", ph->timestamp, ph->id + 1, ph->id);
		pthread_mutex_unlock(ph->message);
		pthread_mutex_lock(ph->right_fork);
		pthread_mutex_unlock(ph->new);
		pthread_mutex_lock(ph->message);
		gettimeofday(&cur_time, NULL);
		ph->timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000 - ph->zero_time;
		if (ph->id + 1 != ph->numb)
			printf("%lld %d has taken a fork %d\n", ph->timestamp, ph->id + 1, ph->id + 1);
		else if (ph->id + 1 == ph->numb)
			printf("%lld %d has taken a fork %d\n", ph->timestamp, ph->id + 1, 0);
		pthread_mutex_unlock(ph->message);
		ft_eat(ph, first_cycle_flag);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		ft_sleep(ph);
		ft_think(ph);
		if (ph->must_eat != 0)
			cycles--;
		first_cycle_flag = 0;
	}
	return (NULL);
}

int	ft_creation(t_lst *data)
{
	int					id;
	int					rv;
	struct timeval		cur_time;
	
	id = 0;
	gettimeofday(&cur_time, NULL);
	data->zero_time = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
	//printf("ZERO: %lld\n", zero);
	//while (id < data->numb)
	//{
	//	data->ph[id].id = id;
	//	data->ph[id].numb = data->numb;
	//	data->ph[id].message = &data->message;
	//	data->ph[id].new = &data->new;
	//	data->ph[id].last_dinner = data->zero_time;
	//	data->ph[id].die_time = data->die_time;
	//	data->ph[id].eat_time = data->eat_time;
	//	data->ph[id].sleep_time = data->sleep_time;
	//	data->ph[id].must_eat = data->must_eat;
	//	data->ph[id].left_fork = &data->mut[id];
	//	if (id + 1 != data->numb)
	//		data->ph[id].right_fork = &data->mut[id + 1];
	//	else if (id + 1 == data->numb)
	//		data->ph[id].right_fork = &data->mut[0];
	//	data->ph[id].zero_time = data->zero_time;
	//	rv = pthread_create(&data->philos[id], NULL, &ft_actions, &data->ph[id]);
	//	if (rv != 0)
	//	{
	//		printf("Error: return code from pthread_create is %d", rv);
	//		return (1);
	//	}
	//	id = id + 2;
	//}
	//id = 1;
	//usleep(100);
	//while (id < data->numb)
	//{
	//	data->ph[id].id = id;
	//	data->ph[id].numb = data->numb;
	//	data->ph[id].message = &data->message;
	//	data->ph[id].new = &data->new;
	//	data->ph[id].last_dinner = data->zero_time;
	//	data->ph[id].die_time = data->die_time;
	//	data->ph[id].eat_time = data->eat_time;
	//	data->ph[id].sleep_time = data->sleep_time;
	//	data->ph[id].must_eat = data->must_eat;
	//	data->ph[id].left_fork = &data->mut[id];
	//	if (id + 1  != data->numb)
	//		data->ph[id].right_fork = &data->mut[id + 1];
	//	else if (id + 1  == data->numb)
	//		data->ph[id].right_fork = &data->mut[0];
	//	data->ph[id].zero_time = data->zero_time;
	//	rv = pthread_create(&data->philos[id], NULL, &ft_actions, &data->ph[id]);
	//	if (rv != 0)
	//	{
	//		printf("Error: return code from pthread_create is %d", rv);
	//		return (1);
	//	}
	//	id = id + 2;
	//}
	while (id < data->numb)
	{
		data->ph[id].id = id;
		data->ph[id].numb = data->numb;
		data->ph[id].message = &data->message;
		data->ph[id].new = &data->new;
		data->ph[id].last_dinner = data->zero_time;
		data->ph[id].die_time = data->die_time;
		data->ph[id].eat_time = data->eat_time;
		data->ph[id].sleep_time = data->sleep_time;
		data->ph[id].must_eat = data->must_eat;
		data->ph[id].left_fork = &data->mut[id];
		if (id + 1  != data->numb)
			data->ph[id].right_fork = &data->mut[id + 1];
		else if (id + 1  == data->numb)
			data->ph[id].right_fork = &data->mut[0];
		data->ph[id].zero_time = data->zero_time;
		id++;
	}
	id = 0;
	while (id < data->numb)
	{
		rv = pthread_create(&data->philos[id], NULL, &ft_actions, &data->ph[id]);
		if (rv != 0)
		{
			printf("Error: return code from pthread_create is %d", rv);
			return (1);
		}
		id = id + 1;
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
		free_mut_array(data, id);
		return (1);
	}
	if (pthread_mutex_init(&data->new, NULL) != 0)
	{
		pthread_mutex_destroy(&data->new);
		pthread_mutex_destroy(&data->message);
		free_mut_array(data, id);
		return (1);
	}
	return (0);
}

void	ft_monitor_death(t_lst *data)
{
	struct timeval		cur_time;
	long long 			timestamp;
	int					i;
	
	//gettimeofday(&cur_time, NULL);
	//timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
	//if (data->numb == 1)
	//{
	//	printf("%lld %d died\n", timestamp - data->zero_time, 1);
	//	exit (0);
	//}
	while (1)
	{
		gettimeofday(&cur_time, NULL);
		timestamp = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
		i = 0;
		while (i < data->numb)
		{
			//printf("philo %d time died %lld\n\n", i + 1, timestamp - data->eat_time - data->ph[i].last_dinner);
			//printf("timestamp %lld\n", timestamp);
			//printf("data->eat_time %d\n", data->eat_time);
			//printf("data->ph[i].last_dinner %lld\n", data->ph[i].last_dinner);
			//printf("data->die_time %d\n", data->die_time);
			if (timestamp - data->eat_time - data->ph[i].last_dinner > data->die_time || ((data->die_time < data->eat_time) && (timestamp - data->zero_time == data->die_time)))
			{
				pthread_mutex_lock(&data->message);
				//printf("\nphilo %d time died %lld\n", i + 1, timestamp - data->eat_time - data->ph[i].last_dinner); //del
				printf("%lld %d died\n", timestamp - data->zero_time, i + 1);
				//printf("philo %d last dinner %lld\n", i + 1, data->ph[i].last_dinner);
				//printf("philo %d timestamp death %lld\n", i + 1, timestamp);
				//printf("philo %d data->die_time %d\n", i + 1, data->die_time);
				pthread_mutex_unlock(&data->message);
				exit (0);
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
	printf("%d\n", data.numb);
	printf("%d\n", data.die_time);
	printf("%d\n", data.eat_time);
	printf("%d\n", data.sleep_time);
	printf("%d\n", data.must_eat);
	if (ft_create_threads(&data) == 1)
	{
		ft_clearing(&data, 1);
		return (ft_putstr_ret("Error\n", 2));
	}
	//else
	//	ft_clearing(&data, 0);
}