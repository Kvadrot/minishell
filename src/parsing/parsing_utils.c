/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/06 19:46:51 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	whitespace[] = " \t\r\n\v";
char	symbols[] = "<|>&;()";

// Returns true when when *s is in toks.
// Function updates *ps to point to the next non-whitespace character.
int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return (*s && strchr(toks, *s));
}

void	panic(char *s)
{
	printf("%s\n", s);
	exit(1);
}

t_cmd	*nulterminate(t_cmd *cmd)
{
	int				i;
	t_backcmd	*bcmd;
	t_execcmd	*ecmd;
	t_listcmd	*lcmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if (cmd == 0)
		return (0);
	switch (cmd->type)
	{
	case EXEC:
		ecmd = (t_execcmd *)cmd;
		for (i = 0; ecmd->argv[i]; i++)
			*ecmd->eargv[i] = 0;
		break ;
	case REDIR:
		rcmd = (t_redircmd *)cmd;
		nulterminate(rcmd->cmd);
		*rcmd->efile = 0;
		break ;
	case PIPE:
		pcmd = (t_pipecmd *)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
		break ;
	case LIST:
		lcmd = (t_listcmd *)cmd;
		nulterminate(lcmd->left);
		nulterminate(lcmd->right);
		break ;
	case BACK:
		bcmd = (t_backcmd *)cmd;
		nulterminate(bcmd->cmd);
		break ;
	}
	return (cmd);
}

/* 
** Function gettoken returns the type of the token found in the string.
** It also updates the pointer to the string to point to the next token.
** It also updates the pointers to the beginning and end of the token.
** It returns the type of the token found.
 */

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	switch (*s)
	{
	case 0:
		break ;
	case '|':
	case '(':
	case ')':
	case ';':
	case '&':
	case '<':
		s++;
		break ;
	case '>':
		s++;
		if (*s == '>')
		{
			ret = '+';
			s++;
		}
		break ;
	default:
		ret = 'a';
		while (s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
			s++;
		break ;
	}
	if (eq)
		*eq = s;

	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return (ret);
}