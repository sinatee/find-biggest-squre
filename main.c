/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisupapi <sisupapi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:24:58 by sisupapi          #+#    #+#             */
/*   Updated: 2026/05/26 21:30:48 by sisupapi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	process_map(char *file_name)
{
	t_map_info	info;
	char		*map;
	int			start;
	int			file_size;

	file_size = get_file_size(file_name);
	map = get_file(file_name);
	if (file_size < 1 || !map)
	{
		write(1, "map error\n", 10);
		free(map);
		return ;
	}
	start = check_map(map, file_size, &info);
	if (start == -1)
		write(1, "map error\n", 10);
	else
		solve_bsq(map, file_size, &info, start);
	free(map);
}

static void	process_stdin(void)
{
	t_map_info	info;
	char		*map;
	int			start;
	int			size;

	map = read_stdin(&size);
	if (!map || size < 1)
	{
		write(1, "map error\n", 10);
		free(map);
		return ;
	}
	start = check_map(map, size, &info);
	if (start == -1)
		write(1, "map error\n", 10);
	else
		solve_bsq(map, size, &info, start);
	free(map);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		process_stdin();
	else
	{
		i = 1;
		while (i < argc)
		{
			process_map(argv[i]);
			if (i < argc - 1)
				write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}
