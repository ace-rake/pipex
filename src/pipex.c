/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:22:55 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/16 12:58:34 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

//return last fd written to
int	pipex(t_data *data)
{
	int	iter;
	int	current_input_fd;
	int	current_output_fd;
	int	result;

	current_input_fd = data->input_fd;
	iter = 0;
	while (iter < data->cmd_amount)
	{
		current_output_fd = -1;
		if (iter == data->cmd_amount - 1)
			current_output_fd = data->output_fd;
		result = execute(&current_input_fd, data->cmds[iter], current_output_fd,
				iter);
		close(current_input_fd);
		if (result == -1)
			exit_handler(0, data);
		iter++;
	}
	return (current_input_fd);
}
