/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:31:50 by ocartier          #+#    #+#             */
/*   Updated: 2024/09/28 11:11:27 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "./ft_printf/includes/libft.h"
# include "./ft_printf/includes/ft_printf.h"

void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *));
#endif
