/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:37:47 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/01 11:54:52 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_cmd_data	*cmd_data_con(char *cmd_line, char *envp[])
{
	t_cmd_data *cmd_data;

	cmd_data = (t_cmd_data *)malloc(sizeof(cmd_data));
	if (!cmd_data)
		exit_handler(0,NULL);
	cmd_data->args = ft_split(cmd_line, ' ');
	cmd_data->cmd_line = cmd_line;
	cmd_data->cmd_path = path_finder(envp, cmd_data->args[0]);
	return (cmd_data);
}

int	opener(char *file, int mode)
{
	int	fd;

	fd = open(file, mode);
	return (fd);
}

t_data *data_init(int argc, char *argv[], char *envp[])
{
	t_data *data;
	int	iter;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_handler(0,data);
	data->cmd_amount = argc - 3;
	if (data->cmd_amount < 2)
		exit_handler(2, data);
	data->cmds = (t_cmd_data **)malloc((data->cmd_amount + 1) * sizeof(t_cmd_data *));
	iter = -1;
	while (++iter < data->cmd_amount)
	{
		data->cmds[iter] = cmd_data_con(argv[iter + 2], envp);
		if (data->cmds[iter] == NULL)
			exit_handler(0, data);
	}
	data->input_fd = opener(argv[1], O_RDONLY);
	data->output_fd = opener(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (data->output_fd == -1 || data->input_fd == -1)
		exit_handler(0, data);
	return (data);
}
