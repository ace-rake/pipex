/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 09:46:59 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/01 11:21:06 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	create_file(char *name)
{
	int fd;

	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		exit_handler(0, NULL);
	return (fd);
}

int	exec_child(int input, t_cmd_data *cmd_data, int output)
{
	if (dup2(input, STDIN_FILENO) == -1 || dup2(output, STDOUT_FILENO))
	{
		close(input);
		close(output);
		exit(errno);
	}
	close(input);
	close(output);
	execve(cmd_data->cmd_path, cmd_data->args, NULL);
	exit(-1);
}

//return output_fd
int	execute(int input_fd, t_cmd_data *cmd_data, int output_fd, int iter)
{
	pid_t child;
	int	child_status;
	char *name;

	name = (ft_strjoin("tmp_file_no_", ft_itoa(iter)));
	if (iter != 0)
	{
		close(input_fd);
		input_fd = open(ft_strjoin("tmp_file_no_", ft_itoa(iter - 1)), O_RDONLY);
	}
	if (output_fd == -1)
		output_fd = create_file(name);
	if ((child = fork()) == -1)
		exit_handler(0, NULL);
	if (child == 0)
		exec_child(input_fd, cmd_data, output_fd);
	waitpid(child, &child_status, 0);
	if (child_status != 0)
	{
		close(output_fd);
		errno = child_status;
		return (-1);
	}
	return (output_fd);
}
