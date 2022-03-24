/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:04:00 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/24 21:04:16 by ayajirob@st      ###   ########.fr       */
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
	free(data->mut);
	data->mut = NULL;
}

int	ft_clearing(t_lst *data, int error_flag)
{
	//free_mut_array(data, data->numb);
	//pthread_mutex_destroy(&data->message);
	//pthread_mutex_destroy(&data->meals);
	if (data->philos != NULL)
		free(data->philos);
	if (data->ph != NULL)
		free(data->ph);
	return (error_flag);
}
