/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:08:48 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/30 17:56:52 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_define_cycles_numb(t_lst *data)
{
	if (data->must_eat != -1)
		data->cycles = data->must_eat;
	else
		data->cycles = 1;
}

static int	ft_check_characters(int ac, char **av)
{
	int	i;
	int	j;

	j = 1;
	while (j < ac)
	{
		i = 0;
		while (av[j][i] != '\0')
		{
			if (ft_isdigit_orsign(av[j][i]) == 0)
				return (1);
			if (i == 0 && av[j][i + 1] == '\0' && \
			(av[j][i] == '+' || av[j][i] == '-'))
				return (1);
			if (i == 0 && (av[j][i + 1] == '+' || av[j][i + 1] == '-') && \
			(av[j][i] == '+' || av[j][i] == '-'))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	ft_parser(int ac, char **av, t_lst *data)
{
	if (ft_check_characters(ac, av) == 1)
		return (1);
	data->numb = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat < 0)
			return (1);
	}
	else if (ac == 5)
		data->must_eat = -1;
	if (data->numb <= 0 || data->die_time < 0 || data->eat_time < 0 || \
	data->sleep_time < 0)
		return (1);
	return (0);
}

int	ft_create_semaphores(t_lst *data)
{
	//sem_unlink("forks");
	//sem_unlink("messages");
	//sem_unlink("general");
	data->forks = sem_open("forks", O_CREAT, S_IRWXU, data->numb);
	if (data->forks == SEM_FAILED)
	{
		return (ft_putstr_ret("Error: sem_open failed\n", 2));
	}
	sem_unlink("forks");
	data->messages = sem_open("messages", O_CREAT, S_IRWXU, 1);
	if (data->messages == SEM_FAILED)
	{
		sem_close(data->forks);
		return (ft_putstr_ret("Error: sem_open failed\n", 2));
	}
	sem_unlink("messages");
	data->general = sem_open("general", O_CREAT, S_IRWXU, 1);
	if (data->general== SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->messages);
		return (ft_putstr_ret("Error: sem_open failed\n", 2));
	}
	sem_unlink("general");
	return (0);
}

int	ft_allocate_memory(t_lst *data)
{
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
