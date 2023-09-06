/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_full_spring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 08:52:36 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/05 11:57:51 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	word_count(char *str, char separator)
{
	int	result;
	int	iter;

	iter = 0;
	result = 0;
	while (str[iter] != '\0')
	{
		while (str[iter] == separator)
			iter++;
		if (str[iter] != '\0' && str[iter] != '\"')
		{
			result++;
			while (str[iter] != separator && str[iter] != '\0')
				iter++;
		}
		else if (str[iter] == '\"')
		{
			result++;
			iter++;
			while (str[iter] != '\"')
				iter++;
			iter++;
		}
	}
	return (result);
}

int	get_next_length(char *str, char separator)
{
	int	result;

	result = 0;
	if (separator == '\"' && str[0] == separator)
		result++;
	while (str[result] != separator)
		result++;
	if (separator == '\"' && str[result] == separator)
		result++;
	return (result);
}

char	*get_word(char *str, char separator)
{
	char	*result;
	int		iter;

	result = (char *)malloc((get_next_length(str, separator) + 1)
			* sizeof(char));
	if (!result)
		return (NULL);
	iter = 0;
	while (str[iter] != separator && str[iter] != '\0')
	{
		result[iter] = str[iter];
		++iter;
	}
	result[iter] = '\0';
	return (result);
}

char	*get_string(char *str)
{
	char	*result;
	int		iter;

	result = (char *)malloc((get_next_length(str, '\"') + 1) * sizeof(char));
	if (!result)
		return (NULL);
	iter = 0;
	while (str[iter] != '\"')
	{
		result[iter] = str[iter];
		++iter;
	}
	result[iter] = '\0';
	return (result);
}

char	**ft_str_full_split(char *str, char separator)
{
	char	**result;
	int		iter;

	result = (char **)malloc((word_count(str, separator) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	iter = -1;
	while (++iter < word_count(str, separator))
	{
		while (*str == separator && *str != '\0')
			str++;
		if (*str == '\"')
			result[iter] = get_string(++str);
		else
			result[iter] = get_word(str, separator);
		if (result[iter] == NULL)
			while (--iter >= 0)
				free(result[iter]);
		if (result[iter] == NULL)
			return (NULL);
		str += ft_strlen(result[iter]);
	}
	result[iter] = NULL;
	return (result);
}
