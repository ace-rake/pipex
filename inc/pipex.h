/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:47:45 by vdenisse          #+#    #+#             */
/*   Updated: 2023/08/30 14:45:13 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/libft/libft.h"

# include <fcntl.h>
# include <errno.h>
# include <string.h>

//needed for perror
# include <stdio.h>


# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>


# ifndef TMPFILE_NAME
#  define TMPFILE_NAME "tmp_file"
# endif
# define OUTPUT 1
# define INPUT 0

typedef struct	s_cmd_data {
	char *cmd_path;
	char *cmd_line;
	char **args;
}				t_cmd_data;

typedef struct s_data {
	t_cmd_data **cmds;
	int	cmd_amount;
	int	input_fd;
	int	output_fd;
}				t_data;

t_data	*data_init(int argc, char *argv[], char *envp[]);
void	exit_handler(int cust_errno, t_data *data);
void	free_data(t_data *data);
void	delete_tmp_files(t_data *data);
char	*path_finder(char *envp[], char *cmd);
int	execute(int input_fd, t_cmd_data *cmd_data, int output_fd, int iter);
int	pipex(t_data *data);
#endif