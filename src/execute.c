/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:22:28 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/01 13:34:13 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/pipex.h"

char	*tmp_file_name_gen(int iter)
{
	char	*name;
	char	*nbr;

	nbr = ft_itoa(iter);
	name = ft_strjoin(TMP_FILE_NAME, nbr);
	free(nbr);
	return (name);
}

int	create_file(int iter)
{
	int		fd;
	char	*name;

	name = tmp_file_name_gen(iter);
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	free(name);
	return (fd);
}

int	exec_child(int input, t_cmd_data *cmd_data, int output)
{
	if (dup2(input, STDIN_FILENO) == -1 || dup2(output, STDOUT_FILENO) == -1)
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
int	execute(int *input_fd, t_cmd_data *cmd_data, int output_fd, int iter)
{
	pid_t	child;
	int		child_status;
	char	*name;

	if (iter != 0)
	{
		name = tmp_file_name_gen(iter - 1);
		close(*input_fd);
		*input_fd = open(name, O_RDONLY);
		free(name);
	}
	if (output_fd == -1)
		output_fd = create_file(iter);
	if (output_fd == -1)
		return (-1);
	if ((child = fork()) == -1)
		return (-1);
	if (child == 0)
		exec_child(*input_fd, cmd_data, output_fd);
	waitpid(child, &child_status, 0);
	if (child_status != 0)
	{
		close(output_fd);
		errno = child_status;
		return (-1);
	}
	return (output_fd);
}
