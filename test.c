#include "inc/pipex.h"

int	main(void)
{
	int fd1 = open("infile", O_RDONLY);
	char buffer[10];
	int	bytes_read = read(fd1, buffer, sizeof(buffer));
	write(1, buffer, bytes_read);
	int fd2 = dup(fd1);




	pid_t child = fork();
	if (child == 0)
	{
		bytes_read = read(fd2, buffer, sizeof(buffer));
		write(1, buffer, bytes_read);
	}
	else
	{
	bytes_read = read(fd1, buffer, sizeof(buffer));
	write(1, buffer, bytes_read);
	}
}
