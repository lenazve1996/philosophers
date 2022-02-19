/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:43:50 by ayajirob          #+#    #+#             */
/*   Updated: 2022/02/19 18:00:42 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (*s++ != '\0')
		length++;
	return (length);
}
