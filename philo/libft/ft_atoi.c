/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:42:38 by ayajirob          #+#    #+#             */
/*   Updated: 2022/02/19 18:00:13 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

long long int	ft_atoi(const char *str)
{
	int				sign;
	long long int	count;

	count = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = sign * -1;
		str++;
	}
	while (*str)
	{
		if ((*str >= '0' && *str <= '9'))
			count = (count * 10) + (*str++ - 48);
		else
			return (count * sign);
	}
	return (count * sign);
}
