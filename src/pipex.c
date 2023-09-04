/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:22:55 by vdenisse          #+#    #+#             */
/*   Updated: 2023/09/01 11:32:07 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//return last fd written to
int	pipex(t_data *data)
{
	int	iter;
	int	current_input_fd;
	int	current_output_fd;
	int	tmp_fd;

	current_input_fd = data->input_fd;
	iter = 0;
	while (iter < data->cmd_amount)
	{
		current_output_fd = -1;
		if (iter == data->cmd_amount - 1)
			current_output_fd = data->output_fd;
		tmp_fd = execute(&current_input_fd, data->cmds[iter], current_output_fd,
				iter);
		close(current_input_fd);
		current_input_fd = tmp_fd;
		if (current_input_fd == -1)
			exit_handler(1, data);
		iter++;
	}
	return (current_input_fd);
}
