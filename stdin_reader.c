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

static char	*expand_buffer(char *old_buf, int old_cap)
{
	char	*new_buf;
	int		i;

	new_buf = malloc(old_cap * 2);
	if (!new_buf)
	{
		free(old_buf);
		return (NULL);
	}
	i = 0;
	while (i < old_cap)
	{
		new_buf[i] = old_buf[i];
		i++;
	}
	free(old_buf);
	return (new_buf);
}

char	*read_stdin(int *size)
{
	char	*buf;
	int		bytes;
	int		cap;

	cap = BUF_SIZE;
	*size = 0;
	buf = malloc(cap);
	if (!buf)
		return (NULL);
	bytes = read(0, buf, cap);
	while (bytes > 0)
	{
		*size += bytes;
		if (*size == cap)
		{
			buf = expand_buffer(buf, cap);
			if (!buf)
				return (NULL);
			cap *= 2;
		}
		bytes = read(0, buf + *size, cap - *size);
	}
	return (buf);
}
