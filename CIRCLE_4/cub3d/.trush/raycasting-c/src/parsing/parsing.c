#include "cub3D.h"

void	file_checker(char *str)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		exit_str("No extension found");
	else if (ft_strncmp(ext, ".cub\0", 5))
		exit_error("invalid file extension", ext);
}

void	parsing(char *str)
{
	int		fd;

	file_checker(str);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_strerr(str, errno);
	close(fd);
	printf("Everything looks good\n");
}
