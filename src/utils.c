/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:46:29 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/25 13:53:27 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//ft_str_full_split util
/*
int	get_next_length(char *str, char separator)
{
	int	result;

	result = 0;
	if (separator == '\"' && str[0] == separator)
		result++;
	while (str[result] != separator && str[result])
		result++;
	if (!str[result])
		return (result);
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
	while (str[iter] != '\"' && str[iter])
	{
		result[iter] = str[iter];
		++iter;
	}
	if (!str[iter])
	{
		free(result);
		return (NULL);
	}
	result[iter] = '\0';
	return (result);
}
int	get_arg(char *result,char separator, char *str)
{
	if (*str == '\"')
	{
		result = get_string(++str);
		return (1);
	}
	else
		result = get_word(str, separator);
	return (0);
}
*/
