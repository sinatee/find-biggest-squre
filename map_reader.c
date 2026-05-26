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

char	*get_file(char *file_name)
{
	int		fd;
	int		size;
	char	*buff;

	size = get_file_size(file_name);
	if (size == -1)
		return (NULL);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buff = allocate_disk_file_to_ram(fd, size);
	if (buff == NULL)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (buff);
}

int	get_file_size(char *file_name)
{
	int		fd;
	int		size;
	int		success_read;
	char	buff[BUF_SIZE];

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	size = 0;
	success_read = read(fd, buff, BUF_SIZE);
	while (success_read > 0)
	{
		size += success_read;
		success_read = read(fd, buff, BUF_SIZE);
	}
	close(fd);
	if (success_read == -1)
		return (-1);
	return (size);
}

char	*allocate_disk_file_to_ram(int fd, int size)
{
	char	*buff;
	int		success_read;

	buff = malloc(size);
	if (buff == NULL)
		return (NULL);
	success_read = read(fd, buff, size);
	if (success_read == -1)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}
