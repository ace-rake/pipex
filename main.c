/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:31:38 by vdenisse          #+#    #+#             */
/*   Updated: 2023/08/29 15:23:20 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* 
 * ----------------------------PLAN-OF-ACTION---------------------------------------
 * are commands and arguments valid
 * 
 * check if files 1 and 2 exist, if file2 doesnt exist i guess we create it
 * create a child for the first cmd and put its outpur into a temporary file
 * create a child for the second cmd, use the tmp file as input and use file2 for output
 */

#include "inc/pipex.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
	if (fd == -1)
		exit_handler(0,NULL);
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
		exit_handler(0, data);
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
	return (data);
}

//cmd_line comes from the original *argv[] and thus does not need to be freed
void	free_data(t_data *data)
{
	int	iter;
	int	jter;
	t_cmd_data **cmds;

	printf("cleanup start\n");
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

void	print_data(t_data *data)
{
	int	iter;
	int	jter;

	printf("\ncmd_amount : [%i]\ninput fd : [%i]\noutput fd : [%i]\n\n", data->cmd_amount, data->input_fd, data->output_fd);
	iter = 0;
	while (iter < data->cmd_amount)
	{
		printf("cmd_line : [%s]\ncmd_path : [%s]\n", data->cmds[iter]->cmd_line, data->cmds[iter]->cmd_path);
		jter = 0;
		printf("args start\n");
		while (data->cmds[iter]->args[jter] != NULL)
		{
			printf("arg [%i] : [%s]\n", jter, data->cmds[iter]->args[jter]);
			jter++;
		}
		printf("args end\n\n");
		iter++;
	}
}

int main(int argc, char *argv[], char *envp[]) {
	t_data *data = NULL;

	data = data_init(argc, argv, envp);
	pipex(data);
//	print_data(data);
	free_data(data);
    return 0;
}

