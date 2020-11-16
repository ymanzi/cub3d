/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:47:20 by ymanzi            #+#    #+#             */
/*   Updated: 2020/01/18 21:17:59 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		free_fct(char **line, char **tmp, int ret)
{
	if (*line != NULL && ret != 0)
	{
		free(*line);
		*line = NULL;
	}
	if (*tmp != NULL)
	{
		free(*tmp);
		*tmp = NULL;
	}
	return (ret);
}
