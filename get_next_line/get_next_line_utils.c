/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:35:54 by xhan              #+#    #+#             */
/*   Updated: 2024/07/02 20:59:26 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *string, int searchedChar)
{
	if (!string)
		return (0);
	while (*string)
	{
		if (*string == (char)searchedChar)
			return ((char *)string);
		string++;
	}
	if (*string == (char)searchedChar)
		return ((char *)string);
	else
		return (NULL);
}

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!left_str)
	{
		left_str = (char *)malloc(sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc((ft_strlen(left_str) + ft_strlen(buff) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (left_str[i])
	{
		str[i] = left_str[i];
		i++;
	}
	while (buff[j])
		str[i++] = buff[j++];
	str[i] = '\0';
	return (free(left_str), str);
}

// add check NULL buff 和 check left_str空字符 ??
// add free (left_str)  at the end??
