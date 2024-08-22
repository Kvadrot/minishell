#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char	*make_tokens(char *string)
{
	char		**tokens_arr;
	char		*token;
	size_t		word_len;
	size_t		i;
	size_t		set_position;

	i = 0;
	while (string[i])
	{
		word_len = 0;
		set_position = i;
		if (string[i] == 34)
		{
			word_len++;
			if (string[i] == '\"')
			{
				token = (char *)malloc(sizeof(char) * word_len + 1);
				return (strncpy(token, string, set_position));
				
			}
		}
	}
	return (0);
}

int	main(void)
{
	char *string = "echo \"testing\"";

	printf("String to be tokenized: %s\n", string);
	make_tokens(string);
	printf("%s\n", make_tokens(string));
	return (0);
}