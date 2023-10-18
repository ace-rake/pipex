/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:37:47 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/18 11:54:42 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_cmd_data	*cmd_data_con(char *str, char *envp[])
{
	t_cmd_data	*cmd_data;

	cmd_data = (t_cmd_data *)malloc(sizeof(t_cmd_data));
	if (!cmd_data)
		exit_handler(0, NULL);
	cmd_data->args = ft_str_full_split(str, ' ', word_count(str, ' '));
	if (cmd_data->args == NULL)
	{
		free_cmd_data(cmd_data);
		return (NULL);
	}
	cmd_data->cmd_line = str;
	cmd_data->cmd_path = path_finder(envp, cmd_data->args[0]);
	if (!cmd_data->args || !cmd_data->cmd_path)
	{
		free_cmd_data(cmd_data);
		return (NULL);
	}
	return (cmd_data);
}

int	opener(char *file, int mode)
{
	int	fd;

	fd = open(file, mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fd);
}

t_data	*data_init(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	int		iter;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_handler(3, data);
	data->cmd_amount = argc - 3;
	if (data->cmd_amount < 1)
		exit_handler(2, data);
	data->cmds = (t_cmd_data **)malloc((data->cmd_amount + 1)
			* sizeof(t_cmd_data *));
	iter = -1;
	while (++iter < data->cmd_amount)
	{
		data->cmds[iter] = cmd_data_con(argv[iter + 2], envp);
		if (data->cmds[iter] == NULL)
			exit_handler(3, data);
	}
	data->input_fd = opener(argv[1], O_RDONLY);
	data->output_fd = opener(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT);
	if (data->output_fd == -1 || data->input_fd == -1)
		exit_handler(3, data);
	return (data);
}
