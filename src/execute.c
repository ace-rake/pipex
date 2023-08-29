/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 09:46:59 by vdenisse          #+#    #+#             */
/*   Updated: 2023/08/29 15:40:12 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	create_file(int truncate)
{
	int fd;
	if (truncate)
		fd = open("test", O_RDWR | O_CREAT | O_TRUNC);
	else
		fd = open("test", O_RDWR);
	if (fd == -1)
		exit_handler(0, NULL);
	if (TMPFILE != 0)
		unlink("test");
	return (fd);
}

int	exec_child(int input, t_cmd_data *cmd_data, int output)
{
	printf("child start\n");

//	output = create_file(0);

	printf("input fd : [%d]\noutput fd : [%d]\n",input, output);	
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);

	close(input);
	close(output);

	execve(cmd_data->cmd_path, cmd_data->args, NULL);
	printf("after execve\n");
	exit(-1);
}

//return output_fd
int	execute(int input_fd, t_cmd_data *cmd_data, int output_fd, int iter)
{
	pid_t child;
	int	child_status;

	if (output_fd == -1)
		output_fd = create_file(1);
	child = fork();
	if (child == 0)
		exec_child(input_fd, cmd_data, output_fd);
	waitpid(child, &child_status, 0);
	if (child_status == -1)
		return (-1);
	return (output_fd);
}
