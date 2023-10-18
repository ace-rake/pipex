/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:22:17 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/18 10:39:58 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

void	print_data(t_data *data)
{
	int	iter;
	int	jter;

	printf("\ncmd_amount : [%i]\ninput fd : [%i]\noutput fd : [%i]\n\n",
		data->cmd_amount,
		data->input_fd,
		data->output_fd);
	iter = 0;
	while (iter < data->cmd_amount)
	{
		printf("cmd_line : [%s]\ncmd_path : [%s]\n", data->cmds[iter]->cmd_line,
			data->cmds[iter]->cmd_path);
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

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	data = NULL;
	data = data_init(argc, argv, envp);
	print_data(data);
	pipex(data);
	delete_tmp_files(data);
	free_data(data);
	return (0);
}
