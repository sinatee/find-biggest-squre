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

int	check_map(char *map, int size, t_map_info *info)
{
	int	pos;

	pos = check_first_line(map, size, info);
	if (pos == -1)
		return (-1);
	if (check_all_rows(map, pos, size, info) == -1)
		return (-1);
	return (pos);
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
		if (first_line_num > 214748364
			|| (first_line_num == 214748364 && (map[i] - '0') > 7))
			return (-1);
		first_line_num = (first_line_num * 10) + (map[i] - '0');
		i++;
	}
	if (first_line_num <= 0)
		return (-1);
	return (first_line_num);
}

static int	is_valid_char(char c, t_map_info *info)
{
	return (c == info->empty || c == info->obstacle || c == '\n');
}

int	check_all_rows(char *map, int pos, int size, t_map_info *info)
{
	int	cur_len;
	int	row;

	cur_len = 0;
	row = 0;
	info->width = 0;
	while (pos < size)
	{
		if (!is_valid_char(map[pos], info))
			return (-1);
		if (map[pos] == '\n')
		{
			if ((cur_len == 0) || (info->width != 0 && cur_len != info->width))
				return (-1);
			if (info->width == 0)
				info->width = cur_len;
			cur_len = 0;
			row++;
		}
		cur_len += (map[pos] != '\n');
		pos++;
	}
	if (row != info->lines || cur_len != 0)
		return (-1);
	return (1);
}
