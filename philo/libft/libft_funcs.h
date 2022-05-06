/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajirob@student.42.fr <ayajirob>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:58:04 by ayajirob@st       #+#    #+#             */
/*   Updated: 2022/05/02 18:39:33 by ayajirob@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FUNCS_H
# define LIBFT_FUNCS_H

# include <stddef.h>
# include <unistd.h>

size_t			ft_strlen(const char *s);
long long int	ft_atoi(const char *str);
int				ft_isdigit_orsign(int ch);
int				ft_putstr_ret(char *s, int fd, int error_numb);

#endif