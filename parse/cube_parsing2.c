/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:41:29 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 14:28:30 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_parsing.h"

int		ft_strlen_nospace(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			j++;
		i++;
	}
	return (j);
}

char	*del_debutspace(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

char	*del_allspace(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (str);
	if (!(new = (char*)malloc(sizeof(*new) * (ft_strlen_nospace(str) + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

int		set_data_nswe(char **data, char *line)
{
	while (*line != '.')
		line++;
	if (ft_strlen(line) < 2)
		return (ft_error("Error texture"));
	if (!(*data = ft_strdup_spec(line)))
		return (0);
	return (1);
}

void	set_data_rgb(int *data1, int *data2, int *data3, char *line)
{
	while (*line == 'F' || *line == 'C' || *line == ' ')
		line++;
	*data1 = ft_atoi(line);
	while ((*line >= '0' && *line <= '9'))
		line++;
	line++;
	*data2 = ft_atoi(line);
	while ((*line >= '0' && *line <= '9'))
		line++;
	line++;
	*data3 = ft_atoi(line);
}
