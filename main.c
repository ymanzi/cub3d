/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:00:29 by ymanzi            #+#    #+#             */
/*   Updated: 2020/02/19 16:19:06 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
**gcc -Wall -Wextra -Werror libmlx.a -framework OpenGL -framework AppKit main.c
*/

int	main(int argc, char **argv)
{
	int ret;

	ret = 2;
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 10))
		ret = global(1, argv[1]);
	else if (argc == 2)
		ret = global(0, argv[1]);
	if (ret == 2)
		return (ft_error("Mauvais fichiers (argv) d'exec"));
	return (1);
}
