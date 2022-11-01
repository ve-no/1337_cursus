#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char	*str;
	char		*line;
	int			readed;

	if(fd < 0)
		return (NULL);
	if (!str)
		ft_strdup(str);
	readed = 1;
	// while (readed > 0 && ft_strc)
	return 0;


}
int main() {
int fd = open("text.txt", O_RDONLY);
char *c = (char *) malloc(10);

int size;
size = read(fd, c, 15);
c[size] = '\0';
printf("%s\t %d", c);
}
