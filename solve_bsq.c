/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisupapi <sisupapi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:36:56 by sisupapi          #+#    #+#             */
/*   Updated: 2026/05/26 21:58:37 by sisupapi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static int	get_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}

static void	fill_dp(char *map, int *dp, t_map_info *i, int start)
{
	int	index;
	int	index_2d;

	i->max_size = 0;
	index = -1;
	while (++index < i->lines * i->width)
	{
		index_2d = start + ((index / i->width) * (i->width + 1))
			+ (index % i->width);
		if (map[index_2d] == i->obstacle)
			dp[index] = 0;
		else if (index < i->width || index % i->width == 0)
			dp[index] = 1;
		else
			dp[index] = get_min(dp[index - 1], dp[index - i->width],
					dp[index - i->width - 1]) + 1;
		if (dp[index] > i->max_size)
		{
			i->max_size = dp[index];
			i->max_index = index_2d;
		}
	}
}

static void	draw_square(char *map, t_map_info *i)
{
	int	r;
	int	c;

	r = 0;
	while (r < i->max_size)
	{
		c = 0;
		while (c < i->max_size)
		{
			map[i->max_index - (r * (i->width + 1)) - c] = i->full;
			c++;
		}
		r++;
	}
}

void	solve_bsq(char *map, int size, t_map_info *info, int start)
{
	int	*dp;

	dp = malloc(sizeof(int) * info->lines * info->width);
	if (!dp)
		return ;
	fill_dp(map, dp, info, start);
	draw_square(map, info);
	write(1, map + start, size - start);
	free(dp);
}
