/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:20:19 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/02/23 18:58:49 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc_complete(size_t count, size_t size)
{
	void				*ptr;
	size_t				tot_size;
	unsigned char		*temp;

	tot_size = count * size;
	if (count && size != (tot_size / count))
		return (NULL);
	ptr = malloc(tot_size);
	if (!ptr)
	{
		return (0);
	}
	temp = ptr;
	while (tot_size--)
		*temp++ = 0;
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && (unsigned char)c != *s)
		s++;
	if ((unsigned char)c == *s)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*joined_str;
	size_t	end_joined_len;

	if (!s1 || !s2)
		return (0);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc(sizeof(char) * (total_len + 1));
	if (!joined_str)
	{
		return (0);
	}
	ft_strlcpy(joined_str, s1, ft_strlen(s1)+1);
	end_joined_len = ft_strlen(joined_str);
	ft_strlcat(joined_str + end_joined_len, s2, ft_strlen(s2)+1);
	return (joined_str);
}

size_t	ft_strlen(const char *s)
{
	size_t	strlen;

	strlen = 0;
	while (s[strlen] != '\0')
	{
		strlen++;
	}
	return (strlen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	maxcopylen;
	size_t	index;

	maxcopylen = 0;
	index = 0;
	while (dst[maxcopylen] != '\0' && maxcopylen < size)
			maxcopylen++;
	while (src[index] != '\0' && (maxcopylen + index + 1) < size)
	{
			dst[maxcopylen + index] = src[index];
			index++;
	}
	if (maxcopylen < size)
			dst[maxcopylen + index] = '\0';
	return (maxcopylen + ft_strlen(src));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[counter] != '\0' && counter < size - 1)
	{
		dst[counter] = src[counter];
		counter++;
	}
	dst[counter] = '\0';
	return (ft_strlen(src));
}
