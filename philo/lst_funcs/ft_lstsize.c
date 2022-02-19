/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:17:53 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/02/18 16:10:58 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_lstsize(t_lst *lst)
{
	int	list_length;

	if (lst == NULL)
		return (0);
	list_length = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		list_length++;
	}
	return (list_length);
}
