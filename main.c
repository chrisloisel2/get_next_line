#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int		main(int ac, char **av)
{
	int		fd;
	int		ret;
	char	*line;

	fd = (ac == 1) ? 0 : open(av[1], O_RDONLY);
	ret = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		printf("%s\n", line);
		free(line);
	}
	free(line);
	close(fd);
	system("leaks a.out");
	return (0);
}
