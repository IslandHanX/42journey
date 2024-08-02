/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:58:01 by xhan              #+#    #+#             */
/*   Updated: 2024/07/02 20:58:04 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>

int		ft_printf(const char *format, ...);
int		prt_str(char const *str);
int		prt_ptr(void *addr);
int		prt_int(int n);
int		prt_unsigned(unsigned int n);
int		prt_hexa(unsigned int nbr, bool upper_case);

#endif