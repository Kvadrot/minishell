#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_skip_whitespace(char **s)
{
	while (*s && **s && strchr(" \t\r\n\v", **s))
		(*s)++;
}

int	main(void)
{
	char	*str = "   \t\n\r\v";
	char	*ptr = "   \t\n\r\v asdasd";

	ft_skip_whitespace(&ptr);
	printf("ptr: %s\n", ptr);
	return (0);
}