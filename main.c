#include <sys/fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
    int		fd;
    char	*line;
    int		i;
    fd = open("files/read_error.txt", O_RDONLY);
    while (i < 6)
    {
        line = get_next_line(fd);
        // printf("line [%02d]: %s", i, line);
        // printf("%s", "\n");
        free(line);
        i++;
    }
    close(fd);
    return (0);
}