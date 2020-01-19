/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 02:20:52 by lchristo          #+#    #+#             */
/*   Updated: 2020/01/19 02:12:30 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_checkfile(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_run_stat(char *stat)
{
	char *leak;

	leak = stat;
	stat = ft_substr(stat, ft_checkfile(stat) + 1, ft_strlen(stat));
	free(leak);
	return (stat);
}

int		get_next_line(int fd, char **line)
{
	char		tmp[BUFFER_SIZE + 1];
	static char	*stat;
	int			ret;
	char		*leak;

	ret = 0;
	if (!stat)
	{
		stat = malloc(sizeof(char) * 1);
		stat[0] = '\0';
	}
	if (ft_checkfile(stat) != -1)
	{
		*line = ft_substr(stat, 0, ft_checkfile(stat));
		stat = ft_run_stat(stat);
		return (1);
	}
	while ((ft_checkfile(stat) == -1) && (ret = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[ret] = '\0';
		leak = stat;
		stat = ft_strjoin(stat, tmp);
		free(leak);
	}
	if (ret > 0)
	{
		*line = ft_substr(stat, 0, ft_checkfile(stat));
		stat = ft_run_stat(stat);
		return (1);
	}
	if (ret == -1)
		return (-1);
	*line = ft_substr(stat, 0, ft_strlen(stat));
	free(stat);
	stat = NULL;
	return (0);
}
