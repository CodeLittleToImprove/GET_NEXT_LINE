// for mandatory part
#include <sys/fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("files/read_error.txt", O_RDONLY);
// 	while (i < 6)
// 	{
// 		line = get_next_line(fd);
// 		// printf("line [%02d]: %s", i, line);
// 		// printf("%s", "\n");
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }

// for bonus part
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "get_next_line_bonus.h"

int	main(void)
{
	int	fd1;
	int	fd2;

	fd1 = open("formyself/files/katze.txt", O_RDONLY);
	fd2 = open("formyself/files/katze2.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("open");
		exit(1);
	}
	char *line1 = NULL;
	char *line2 = NULL;
	while (1)
	{
		if (line1 == NULL)
		{
			line1 = get_next_line(fd1);
			if (line1 == NULL)
			{
				close(fd1);
				fd1 = -1;
			}
		}
		if (line2 == NULL)
		{
			line2 = get_next_line(fd2);
			if (line2 == NULL)
			{
				close(fd2);
				fd2 = -1;
			}
		}
		if (line1 != NULL)
		{
			printf("fd1: %s\n", line1);
			free(line1);
			line1 = NULL;
		}
		if (line2 != NULL)
		{
			printf("fd2: %s\n", line2);
			free(line2);
			line2 = NULL;
		}
		if (fd1 == -1 && fd2 == -1)
			break ;
	}
	return (0);
}
