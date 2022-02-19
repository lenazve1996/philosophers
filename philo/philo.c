/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:24:14 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/02/19 19:23:44 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_ret(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	return (1);
}

int	ft_parser(int ac, char **av, t_lst **data)
{
	(*data)->philo = ft_atoi(av[1]); 
	(*data)->die_time = ft_atoi(av[2]); 
	(*data)->eat_time = ft_atoi(av[3]); 
	(*data)->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		(*data)->must_eat = ft_atoi(av[5]); 
	return (0);
}


int	main(int argc, char **argv)
{
	t_lst *data;
	
	if (argc < 5)
		return (ft_putstr_ret("Error", 2));
	if (ft_parser(argc, argv, &data) == 1)
		return (ft_putstr_ret("Error", 2));
	
}