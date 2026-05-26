/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sisupapi <sisupapi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:38:34 by sisupapi          #+#    #+#             */
/*   Updated: 2026/05/26 22:03:29 by sisupapi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUF_SIZE 4096

typedef struct s_map_info
{
	int		lines;
	char	empty;
	char	obstacle;
	char	full;
}	t_map_info;

// file reader
char	*get_file(char *file_name);
int		get_file_size(char *file_name);
char	*allocate_disk_file_to_ram(int fd, int size);

#endif