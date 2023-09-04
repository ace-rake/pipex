/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:39:46 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/01 12:51:52 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//cmd_line comes from the original *argv[] and thus does not need to be freed

void	free_cmd_data(t_cmd_data *cmd_data)
{
	int	iter;

	if (!cmd_data)
		return ;
	iter = 0;
	if (cmd_data->cmd_path)
		free(cmd_data->cmd_path);
	if (cmd_data->args)
	{
		while (cmd_data->args[iter])
			free(cmd_data->args[iter++]);
		free(cmd_data->args);
	}
	free(cmd_data);
}

void	free_data(t_data *data)
{
	int			iter;
	t_cmd_data	**cmds;

	cmds = data->cmds;
	iter = 0;
	if (cmds)
		while (iter < data->cmd_amount)
		{
			free_cmd_data(data->cmds[iter]);
			iter++;
		}
	free(cmds);
	free(data);
}
char	*tmp_file_name_gen(int iter);
void	delete_tmp_files(t_data *data)
{
	int		iter;
	char	*name;

	iter = 0;
	while (iter < data->cmd_amount - 1)
	{
		name = tmp_file_name_gen(iter);
		unlink(name);
		free(name);
		iter++;
	}
}
