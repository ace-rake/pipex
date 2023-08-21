/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:31:38 by vdenisse          #+#    #+#             */
/*   Updated: 2023/08/21 14:49:02 by vdenisse         ###   ########.fr       */
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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {


    // Create a buffer to capture the output of the 'which' command
    char buffer[1024];

    // Command to run
    char *cmd = "which";
    char *arg = "which"; // Replace with the command you're searching for

    // Set up arguments for execve
    char *args[3];
	args[0] = cmd;
	args[1] = arg;
	args[2] = NULL;
    char *envp[] = {NULL};

    // Create a pipe to capture 'which' command output
	/*
	 * [0] is for reading
	 * [1] is for writing
	 */

	int fd[2];
	pipe(fd);
	

    // Fork a child process
    pid_t child_pid = fork();

	if (child_pid == 0)
	{
		printf("Child start\n");
		dup2(fd[1], STDOUT_FILENO);
		execve("/usr/bin/which",args, envp);
		close(fd[0]);
		write(fd[1], "test\0", 5);
		close(fd[1]);
		printf("Child end\n");
		exit(0);
	}
	else
	{
		printf("Parent start\n");
		int status;
		close(fd[1]);
		wait(&status);
		char line[1024];
		int bytes_read = read(fd[0], line, 1024);
		printf("child exit with [%d]\nread from pipe [%s]\n", status, line);
		
		printf("Parent end\n");
	}


    return 0;
}

