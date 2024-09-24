/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:53 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/09/24 15:47:03 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Returns true when when *s is in toks.
// Function updates *ps to point to the next non-whitespace character.
int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s && *s && strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (*s && strchr(toks, *s));
}


// t_cmd	*nulterminate(t_cmd *cmd)
// {
// 	t_backcmd	*bcmd;
// 	t_listcmd	*lcmd;
// 	t_pipecmd	*pcmd;
// 	t_redircmd	*rcmd;

// 	if (cmd == 0)
// 		return (0);
// 	switch (cmd->type)
// 	{
// 	case REDIR:
// 		rcmd = (t_redircmd *)cmd;
// 		nulterminate(rcmd->cmd);
// 		*rcmd->efile = 0;
// 		break ;
// 	case INREDIR:
// 		rcmd = (t_redircmd *)cmd;
// 		nulterminate(rcmd->cmd);
// 		*rcmd->efile = 0;
// 		break ;
// 	case PIPE:
// 		pcmd = (t_pipecmd *)cmd;
// 		nulterminate(pcmd->left);
// 		nulterminate(pcmd->right);
// 		break ;
// 	case LIST:
// 		lcmd = (t_listcmd *)cmd;
// 		nulterminate(lcmd->left);
// 		nulterminate(lcmd->right);
// 		break ;
// 	case BACK:
// 		bcmd = (t_backcmd *)cmd;
// 		nulterminate(bcmd->cmd);
// 		break ;
// 	}
// 	return (cmd);
// }

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
	while (s < es && strchr(" \t\r\n\v", *s))
		s++;
	if (q)
		*q = s;
	ret = *s;

	if (*s == 0)
		return (0);
	else if (peek(&s, es, "|();&"))
		s++;
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			ret = '+';
			s++;
		}
	}
	else if (*s == '<')
	{
		s++;
		if (*s == '<')
		{
			ret = '-';
			s++;
			*ps = s;
		}
	}
	else
		ret = 'a';

	while (s < es && !strchr(" \t\r\n\v", *s) && !strchr("<|>&;()", *s))
		s++;
	if (eq)
		*eq = s;

	while (s < es && strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (ret);
}