/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 09:37:31 by ymanzi            #+#    #+#             */
/*   Updated: 2020/01/18 21:17:39 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

static char		*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == 0 && s2 == 0)
		return (NULL);
	if (!(ptr = (char*)malloc(sizeof(*ptr) * (ft_strlen(s1)
						+ ft_strlen(s2) + 1))))
		return (NULL);
	while (*(s1 + i))
		ptr[j++] = *(s1 + i++);
	i = 0;
	while (*(s2 + i))
		ptr[j++] = *(s2 + i++);
	ptr[j] = '\0';
	free(s1);
	s1 = NULL;
	return (ptr);
}

static char		*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen((char*)s) < start)
		len = 0;
	if (s == 0 || !(ptr = (char*)malloc(sizeof(*ptr) * (len + 1))))
		return (NULL);
	while (len-- > 0 && *(s + start + i))
	{
		ptr[i] = s[start + i];
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

static void		creat_str_nl(char *s1, char **tmp, char **line, int *ret)
{
	int i;

	if (*ret != -1)
	{
		i = find_line(s1);
		if (i > 0)
		{
			*line = ft_substr(s1, 0, i);
			*tmp = ft_substr(s1, i + 1, ft_strlen(s1) - i - 1);
		}
		else if (i < 0)
		{
			*line = ft_substr(s1, 0, ft_strlen(s1));
			*tmp = ft_substr(s1, ft_strlen(s1) + 2, 100);
		}
		else
		{
			*line = ft_substr(s1, ft_strlen(s1) + 2, 1);
			*tmp = ft_substr(s1, 1, ft_strlen(s1) - 1);
		}
		free(s1);
		s1 = NULL;
	}
	if (*line == NULL || *tmp == NULL)
		*ret = -1;
}

int				get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*tmp[OPEN_MAX] = {0};
	int				ret;

	ret = 1;
	if (!line || fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	if (!tmp[fd])
	{
		if (!(tmp[fd] = (char*)malloc(sizeof(char))))
			return (-1);
		tmp[fd][0] = '\0';
	}
	while (find_line(tmp[fd]) == -1 && (ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!(tmp[fd] = ft_strjoin(tmp[fd], buf)))
			return (free_fct(line, &tmp[fd], -1));
	}
	creat_str_nl(tmp[fd], &tmp[fd], line, &ret);
	if (ret == -1)
		return (free_fct(line, &tmp[fd], -1));
	return ((ret > 0 ? 1 : free_fct(line, &tmp[fd], 0)));
}
