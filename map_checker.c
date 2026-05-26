/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisupapi <sisupapi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:56:18 by sisupapi          #+#    #+#             */
/*   Updated: 2026/05/26 22:40:13 by sisupapi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	check_map(char *map)
{
	
}

// check if the first line is valid
// get value to info
int	check_first_line(char *map, int size, t_map_info *info)
{
	int	first_line_len;

	first_line_len = 0;
	while (first_line_len < size && map[first_line_len] != '\n')
		first_line_len++;
	if (first_line_len == size || first_line_len < 4)
		return (-1);
	info->full = map[first_line_len - 1];
	info->obstacle = map[first_line_len - 2];
	info->empty = map[first_line_len - 3];
	if (info->empty < 32 || info->empty > 126
		|| info->obstacle < 32 || info->obstacle > 126
		|| info->full < 32 || info->full > 126)
		return (-1);
	if ((info->empty == info->obstacle) || (info->empty == info->full)
		|| (info->obstacle == info->full))
		return (-1);
	info->lines = get_num_first_line(map, first_line_len);
	if (info->lines == -1)
		return (-1);
	return (first_line_len + 1);
}

// return num in first line
int	get_num_first_line(char *map, int first_line_len)
{
	int	i;
	int	first_line_num;

	i = 0;
	first_line_num = 0;
	while (i < first_line_len - 3)
	{
		if (map[i] < '0' || map[i] > '9')
			return (-1);
		first_line_num = (first_line_num * 10) + (map[i] - '0');
		i++;
	}
	if (first_line_num <= 0)
		return (-1);
	return (first_line_num);
}

int	check_all_rows(char *map, int pos, int size, t_map_info *info)
{
	int	old_len;
	int	cur_len;
	int	row;

	old_len = -1;
	cur_len = 0;
	row = 0;
	while (pos < size)
	{
		if (map[pos] == '\n')
		{
			if ((cur_len == 0) || (old_len != -1 && old_len != cur_len))
				return (-1);
			old_len = cur_len;
			cur_len = 0;
			row++;
		}
		else if ((map[pos] != info->empty) && map[pos] != info->obstacle)
			return (-1);
		else
			cur_len++;
		pos++;
	}
	if (row != info->lines || cur_len != 0)
		return (-1);
	return (1);
}
