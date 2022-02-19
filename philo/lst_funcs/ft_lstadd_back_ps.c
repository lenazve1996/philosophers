/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_ps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:30:55 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/02/18 16:10:40 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_lstadd_back_ps(t_lst **lst, t_lst *new)
{
	t_lst	*last_elem;

	if (new != NULL && lst != NULL && *lst != NULL)
	{
		last_elem = ft_lstlast_ps(*lst);
		last_elem->next = new;
	}
	else if (*lst == NULL)
	{
		ft_lstadd_front_ps(lst, new);
	}
}
