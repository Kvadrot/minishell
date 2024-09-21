#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	skip_whitespace(char **s, char *es)
{
	while (*s < es && strchr(" \t\r\n\v", **s))
		(*s)++;
}

int	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}


 char	*get_block(char **ps, char *es)
{
	char	*ret;
	char	*s;
	size_t	length;
	char	*start;
	char	quote;

	s = *ps;
	quote = *s;
	length = 0;
	start = s;
	s++;
	while (s < es && *s != quote)
		s++;
	length = s - start +1;
	ret = malloc(length + 1);
	if (ret == NULL)
		return (NULL);
	strncpy(ret, start, length);
	ret[length] = '\0';
	if (quote)
		s++;
	*ps = s;
	return (ret);
} 

char	*get_word(char **ps, char *es)
{
	char	*ret;
	char	*s;
	size_t	length;
	char	*start;

	s = *ps;
	length = 0;
	start = s;
	while (s < es && !ft_iswhitespace(*s))
		s++;
	length = s - start;
	ret = malloc(length + 1);
	if (ret == NULL)
		return (NULL);
	strncpy(ret, start, length);
	ret[length] = '\0';
	*ps = s;
	return (ret);
}

char	*get_string(char **ps, char *es)
{
	skip_whitespace(ps, es);
	if (**ps == '"' || **ps == '\'')
		return (get_block(ps, es));
	else
		return (get_word(ps, es));
}

int	main(void)
{
	char	*input;
	char	*es;
	char	*ps;
	char	*string;

	input = " '  			\"  Hello, World!' \"' ";
	es = input + strlen(input);
	ps = input;
	string = get_string(&ps, es);
	printf("String: %s\n", string);
	free(string);
	return (0);
}

