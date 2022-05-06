/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:08:48 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/05/02 18:48:44 by ayajirob@st      ###   ########.fr       */
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

static int	characters_not_valid(int ac, char **av)
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
				return (PARSER_ERROR);
			if (i == 0 && av[j][i + 1] == '\0' && \
			(av[j][i] == '+' || av[j][i] == '-'))
				return (PARSER_ERROR);
			if (i == 0 && (av[j][i + 1] == '+' || av[j][i + 1] == '-') && \
			(av[j][i] == '+' || av[j][i] == '-'))
				return (PARSER_ERROR);
			i++;
		}
		j++;
	}
	return (0);
}

int	define_meals_number(int ac, char **av, t_lst *data)
{
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat < 0)
			return (PARSER_ERROR);
	}
	else if (ac == 5)
		data->must_eat = -1;
	return (0);
}

int	arguments_not_valid(t_lst *data)
{
	if (data->numb <= 0 || data->die_time < 0 || data->eat_time < 0 || \
	data->sleep_time < 0)
		return (PARSER_ERROR);
	return (0);
}

void	read_program_arguments(char **av, t_lst *data)
{
	data->numb = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
}

int	arguments_number_not_valid(int argc)
{
	if (argc != 5 && argc != 6)
	{
		return (ft_putstr_ret("Error\n", 2, PARSER_ERROR));
	}
	return (0);
}

int	parser(int ac, char **av, t_lst *data)
{
	if (arguments_number_not_valid(ac))
		return (PARSER_ERROR);
	if (characters_not_valid(ac, av))
		return (PARSER_ERROR);
	read_program_arguments(av, data);
	if (arguments_not_valid(data))
		return (PARSER_ERROR);
	if (define_meals_number(ac, av, data) == PARSER_ERROR)
		return (PARSER_ERROR);
	return (0);
}
