/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:31:38 by vdenisse          #+#    #+#             */
/*   Updated: 2023/08/30 15:05:53 by vdenisse         ###   ########.fr       */
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
	delete_tmp_files(data);
	free_data(data);
    return 0;
}

