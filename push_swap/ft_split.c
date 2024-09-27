/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:58:28 by xhan              #+#    #+#             */
/*   Updated: 2024/09/18 15:03:27 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_separator(char c, char a)
{
	return (c == a);
}

int	count_words(const char *str, char c)
{
	int	words;

	words = 0;
	while (*str)
	{
		while (*str && is_separator(*str, c))
			str++;
		if (*str && !is_separator(*str, c))
		{
			words++;
			while (*str && !is_separator(*str, c))
				str++;
		}
	}
	return (words);
}

char	*malloc_word(const char *start, int length)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (length + 1));
	if (!word)
		return (NULL);
	while (i < length)
	{
		word[i] = start[i];
		i++;
	}
	word[length] = '\0';
	return (word);
}

int	fill_array(char **array, const char *s, char c)
{
	int		i;
	char	*start;

	i = 0;
	while (*s)
	{
		while (*s && is_separator(*s, c))
			s++;
		start = (char *)s;
		while (*s && !is_separator(*s, c))
			s++;
		if (s > start)
		{
			array[i] = malloc_word(start, s - start);
			if (!array[i])
				return (0);
			i++;
		}
	}
	array[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word_count;
	int		success;
	int		i;

	word_count = count_words(s, c);
	array = malloc(sizeof(char *) * (word_count + 1));
	if (!array)
		return (NULL);
	success = fill_array(array, s, c);
	if (!success)
	{
		i = 0;
		while (i < word_count && array[i])
			free(array[i++]);
		free(array);
		return (NULL);
	}
	return (array);
}
