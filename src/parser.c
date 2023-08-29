/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:25:39 by vdenisse          #+#    #+#             */
/*   Updated: 2023/08/22 13:28:26 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char *cmd_path_finder(char **args)
{
	int fd[2];
	pipe(fd);
	pid_t child_pid = fork();
	if (child_pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve("/usr/bin/which", args, NULL);
	}
	return (NULL);
}

t_cmd_data *cmd_parser(char *cmd_str)
{
	t_cmd_data *cmd_data;
	pid_t child_pid = fork();
	cmd_data = (t_cmd_data *)malloc(sizeof(t_cmd_data));
	(void)child_pid;


	return (cmd_data);
}

t_data	*parser(int argc, char *argv[])
{
	t_data *data;
	int iter;

	data = NULL;
	iter = 0;
	data = (t_data *)malloc(sizeof(t_data*));
	data->cmds = (t_cmd_data **)malloc(sizeof(t_cmd_data *) * argc - 1 + 1);
	while (iter < argc)
	{
		data->cmds[iter] = cmd_parser(argv[iter + 1]);
		iter++;
	}

	return (data);
}
