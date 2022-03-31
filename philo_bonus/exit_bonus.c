/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:51:33 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/03/31 13:35:09 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_semaphores(t_lst *data)
{
	sem_close(data->forks);
	sem_close(data->messages);
	sem_close(data->general);
}

void	ft_cleaning(t_lst *data)
{
	ft_close_semaphores(data);
	if (data->children_pids != NULL)
		free(data->children_pids);
}

static void	ft_kill_all_philos(t_lst *data)
{		
	int	n;

	n = 0;
	while (n < data->numb)
	{
		kill(data->children_pids[n], SIGKILL);
		n++;
	}
}

void	ft_wait_philos(t_lst *data)
{
	int				n;
	int				status;

	n = 0;
	while (n < data->numb)
	{
		wait(&status);
		if (status == 768)
		{
			ft_kill_all_philos(data);
			return ;
		}
		n++;
	}
}
