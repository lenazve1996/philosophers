/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:16:49 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/05/02 18:39:56 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

int	ft_putstr_ret(char *s, int fd, int error_numb)
{
	write(fd, s, ft_strlen(s));
	return (error_numb);
}
