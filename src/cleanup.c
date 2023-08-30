/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:39:46 by vdenisse          #+#    #+#             */
/*   Updated: 2023/08/30 14:40:55 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//cmd_line comes from the original *argv[] and thus does not need to be freed
void	free_data(t_data *data)
{
	int	iter;
	int	jter;
	t_cmd_data **cmds;

	cmds = data->cmds;
	iter = 0;
	while (iter < data->cmd_amount)
	{
		if (cmds[iter]->cmd_path)
			free(cmds[iter]->cmd_path);
		jter = 0;
		while (cmds[iter]->args[jter] != NULL)
		{
			free(cmds[iter]->args[jter]);
			jter++;
		}
		free(cmds[iter]->args);
		free(cmds[iter]);
		iter++;
	}
	free(cmds);
	free(data);
}

void	delete_tmp_files(t_data *data)
{
	int	iter;
	char *name;

	iter = 0;
	while (iter < data->cmd_amount - 1)
	{
		name = ft_strjoin("tmp_file_no_", ft_itoa(iter));
		unlink(name);
		free(name);
		iter++;
	}
}
