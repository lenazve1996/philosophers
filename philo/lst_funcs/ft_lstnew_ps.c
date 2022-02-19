/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_ps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:44:01 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/02/18 16:10:56 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_lst	*ft_lstnew_ps(int numb)
{
	t_lst	*new_element;

	new_element = (t_lst *)malloc(sizeof(t_lst));
	if (!new_element)
		return (NULL);
	new_element->numb = numb;
	new_element->up = -1;
	new_element->move = -1;
	new_element->sum = -1;
	new_element->index = -1;
	new_element->next = NULL;
	return (new_element);
}
