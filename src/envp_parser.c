/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:30:24 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/04 13:44:27 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*env_var_finder(char *envp[], char *var_to_find)
{
	int	iter;

	iter = 0;
	while (envp[iter] != NULL)
	{
		if (ft_strncmp(envp[iter], var_to_find, ft_strlen(var_to_find)) == 0)
			return (envp[iter]);
		++iter;
	}
	return (NULL);
}

int	path_length(char *all_path)
{
	int	result;

	result = 0;
	while (all_path[result] != ':' && all_path[result] != '\0')
		result++;
	return (result);
}

char	*find_next_path(char **all_path, char *cmd)
{
	char	*curr_path;
	int		iter;
	char	*tmp_path;
	char	*extension;

	tmp_path = (char *)malloc(path_length(*all_path));
	if (!tmp_path)
		return (NULL);
	iter = 0;
	while (**all_path != ':' && **all_path != '\0')
	{
		tmp_path[iter] = **all_path;
		(*all_path)++;
		iter++;
	}
	if (**all_path != '\0')
		(*all_path)++;
	extension = ft_strjoin("/", cmd);
	curr_path = ft_strjoin(tmp_path, extension);
	free(extension);
	free(tmp_path);
	return (curr_path);
}

//all path in this context is a pointer to the envp PATH= and thus does not need to be freed

char	*path_finder(char *envp[], char *cmd)
{
	char	*all_path;
	char	*curr_path;

	all_path = env_var_finder(envp, "PATH=");
	if (!all_path || all_path + 5 == NULL)
		return (NULL);
	all_path += 5;
	while (1)
	{
		curr_path = find_next_path(&all_path, cmd);
		if (!curr_path)
			return (NULL);
		if (access(curr_path, X_OK) == 0)
		{
			errno = 0;
			break ;
		}
		free(curr_path);
		if (*all_path == '\0')
			return (NULL);
	}
	return (curr_path);
}
