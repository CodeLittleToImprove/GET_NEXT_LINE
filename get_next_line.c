/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:18:16 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/02/22 19:06:28 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_newline_pos(const char *str)
{
	size_t	char_index;

	char_index = 0;
	while (str[char_index] && str[char_index] != '\n')
		char_index++;
	return (char_index);
}

char	*remove_old_string_from_rest_buffer(char *rest_buffer)
{
	char	*cleaned_restbuffer;
	size_t	char_index;
	size_t	newline_pos;
	size_t	past_new_line;
	size_t	cleaned_buffer_len;

	char_index = 0;
	newline_pos = find_newline_pos(rest_buffer);
	if (rest_buffer[newline_pos] == '\0')
	{
		free(rest_buffer);
		return (NULL);
	}
	past_new_line = 1;
	cleaned_buffer_len = (ft_strlen(rest_buffer)) - newline_pos;
	cleaned_restbuffer = ft_calloc_complete(cleaned_buffer_len + 1, sizeof(char));
	while (rest_buffer[newline_pos + past_new_line])
	{
		cleaned_restbuffer[char_index] = rest_buffer[newline_pos + past_new_line];
		char_index++;
		past_new_line++;
	}
	cleaned_restbuffer[char_index] = '\0';
	free(rest_buffer);
	return (cleaned_restbuffer);
}

char	*extract_line_up_to_new_line(char *rest_buffer)
{
	char		*line;
	size_t		char_index;
	size_t		offset;

	char_index = 0;
	offset = 1;
	if (rest_buffer[0] == '\0')
		return (NULL);
	char_index = find_newline_pos(rest_buffer);
	if (rest_buffer[char_index] == '\n')
		offset = 2;
	else
		offset = 1;
	line = ft_calloc_complete(char_index + offset, sizeof(char));
	char_index = 0;
	while (rest_buffer[char_index] != '\n' && rest_buffer[char_index])
	{
		line[char_index] = rest_buffer[char_index];
		char_index++;
	}
	if (rest_buffer[char_index] == '\n')
		line[char_index++] = '\n';
	return (line);
}

char	*ft_concatenate_and_free(char *previous_read, char *current_read)
{
	char	*complete_line;

	complete_line = ft_strjoin(previous_read, current_read);
	free(previous_read);
	return (complete_line);
}

char	*read_file(int fd, char *line_read)
{
	char		*read_buffer;
	ssize_t		bytes_read;

	if (!line_read)
	{
		line_read = ft_calloc_complete(1, sizeof(char));
		if (!line_read)
		{
			free(line_read);
			return (NULL);
		}
	}
	read_buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		line_read = ft_concatenate_and_free(line_read, read_buffer);
		if (ft_strchr(read_buffer, '\n'))
			break ;
	}
	free(read_buffer);
	return (line_read);
}
// line_read holds the read content of a file by line line
// line_read holds the read content until eof or the first \n is encountered but it can also include a string containing \n because the the read buffer does not stop when \n is encountered. 
// That means breaks out of the loop only stops after the first \n is encountered.

// for bonus use a big array and pass the fd to it
char	*get_next_line(int fd)
{
	static char	*rest_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (rest_buffer)
		{
			free(rest_buffer);
			rest_buffer = 0;
		}
		return (NULL);
	}
	rest_buffer = read_file(fd, rest_buffer);
	if (!rest_buffer)
	{
		// rest_buffer = 0;
		return (NULL);
	}
	line = extract_line_up_to_new_line(rest_buffer);
	rest_buffer = remove_old_string_from_rest_buffer(rest_buffer);
	return (line);
}
// in the end the rest_buffer stores the remainder of what was read but not printed. 





// int	main(void)
// {
// // 	char	*line;
// // 	int		i;
// int		fd;
// char	*temp;
// // 	int		fd2;
// // 	int		fd3;
// fd = open("tests/katze.txt", O_RDONLY);
// // 	fd2 = open("tests/katze2.txt", O_RDONLY);
// // 	fd3 = open("tests/katze3.txt", O_RDONLY);
// // 	i = 1;
// // 	while (i < 7)
// // 	{
// // 		line = get_next_line(fd);
// // 		printf("line [%02d]: %s", i, line);
// // 		free(line);
// // 		line = get_next_line(fd2);
// // 		printf("line [%02d]: %s", i, line);
// // 		free(line);
// // 		line = get_next_line(fd3);
// // 		printf("line [%02d]: %s", i, line);
// // 		free(line);
// // 		i++;
// // 	}
// // printf("%s", get_next_line(fd));
// // printf("%s", get_next_line(fd));
// // printf("%s", get_next_line(fd));
// // printf("%s", get_next_line(fd));
// // printf("%s", get_next_line(fd));
// temp = get_next_line(fd);
// // temp = get_next_line(fd);
// printf("%s", temp);
// close(fd);

// // 	close(fd2);
// // 	close(fd3);
// // 	return (0);
// }

// old version
// char	*get_next_line(int fd)
// {
// 	char	*line;
// 	static char	*buffer;
// 	ssize_t	cursor;
// 	size_t	read_bytes;
// 	size_t flag;


// 	cursor = 0;
// 	line = malloc(1000);
// 	flag = 0;
// 	buffer = malloc(BUFFER_SIZE + 1);
// 	while (flag != 1)
// 	{
// 		read_bytes = read(fd, &buffer, BUFFER_SIZE);
// 		if (read_bytes == 0)
// 		{
// 			flag = 1;
// 			break;
// 		}
// 		while (cursor < read_bytes)
// 		{
// 			if (buffer[cursor] = '\n')
// 			{
// 				flag = 1;
// 				break;
// 			}	
// 			buffer[cursor] = line[cursor];	
// 			cursor++;
// 		}
// 		if (read_bytes < BUFFER_SIZE)
// 				flag = 1;
// 	}
// 	return (line);
// }

// int main(int argc, char **argv)
// {
//     int fd;
//     char *line;

//     if (argc == 2)
//     {
//         fd = open(argv[1], O_RDONLY);
//         while ((line = get_next_line(fd)) != NULL)
//         {
//             printf("%s\n", line);
//             free(line);
//         }
//         close(fd);
//     }
//     return 0;
// }

