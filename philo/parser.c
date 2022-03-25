/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:08:48 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/25 18:11:27 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
