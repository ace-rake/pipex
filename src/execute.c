/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:22:28 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/18 11:56:03 by vdenisse         ###   ########.fr       */
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

int	set_fd(int *input_fd, int *output_fd, int iter)
{
	char	*name;

	if (iter != 0)
	{
		name = tmp_file_name_gen(iter - 1);
		close(*input_fd);
		*input_fd = open(name, O_RDONLY);
		free(name);
	}
	if (*output_fd == -1)
		*output_fd = create_file(iter);
	if (*output_fd == -1)
		return (-1);
	return (0);
}

int	check_child(int child_status)
{
	if (WIFEXITED(child_status))
	{
		child_status = WEXITSTATUS(child_status);
		if (child_status != 0)
		{
			errno = child_status;
			return (-1);
		}
	}
	return (0);
}

int	execute(int *input_fd, t_cmd_data *cmd_data, int output_fd, int iter)
{
	pid_t	child;
	int		child_status;

	if (set_fd(input_fd, &output_fd, iter))
		return (-1);
	child = fork();
	if (child == -1)
	{
		close(*input_fd);
		close(output_fd);
		return (-1);
	}
	if (child == 0)
		exec_child(*input_fd, cmd_data, output_fd);
	waitpid(child, &child_status, 0);
	close(*input_fd);
	close(output_fd);
	if (check_child(child_status))
		return (4);
	return (0);
}
