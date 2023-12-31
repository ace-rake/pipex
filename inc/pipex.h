/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:47:45 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/18 13:32:39 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/libft/header/libft.h"
//errno
# include <errno.h>

//open
# include <fcntl.h>

//needed for perror
# include <stdio.h>

//waitpid
# include <sys/wait.h>

//S_IRUSR, macro for rights of created files
# include <sys/stat.h>

//# include <stdlib.h>
//# include <string.h>
//# include <unistd.h>

# ifndef TMP_FILE_NAME
#  define TMP_FILE_NAME "/tmp/tmp_file_no_"
# endif
# define OUTPUT 1
# define INPUT 0

typedef struct s_cmd_data
{
	char		*cmd_path;
	char		*cmd_line;
	char		**args;
}				t_cmd_data;

typedef struct s_data
{
	t_cmd_data	**cmds;
	int			cmd_amount;
	int			input_fd;
	int			output_fd;
}				t_data;

t_data			*data_init(int argc, char *argv[], char *envp[]);
void			exit_handler(int cust_errno, t_data *data);
void			free_cmd_data(t_cmd_data *cmd_data);
void			free_data(t_data *data);
void			delete_tmp_files(t_data *data);
char			*path_finder(char *envp[], char *cmd);
int				execute(int *input_fd, t_cmd_data *cmd_data, int output_fd,
					int iter);
int				pipex(t_data *data);
char			**ft_str_full_split(char *str, char separator, int words);
int				word_count(char *str, char separator);
int				get_arg(char *result, char separator, char *str);
char			*tmp_file_name_gen(int iter);
int				create_file(int iter);
#endif
