/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:26:25 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/21 18:21:25 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"

t_red	*init_red(int flg)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	red->file_name = NULL;
	red->flag = flg;
	return (red);
}

t_list	*init_lst(void)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	lst->content = NULL;
	lst->next = NULL;
	return (lst);
}

void	remove_s_d_qoute(char **buffer)
{
	char	*tmp;
	char *to_free;

	if (buffer)
	{
		if ((*buffer)[0] == '"' || (*buffer)[0] == '\'')
		{
		to_free=*buffer;
			(*buffer)++;
			tmp = malloc(sizeof(char) * ft_strlen(*buffer));
			ft_strlcpy(tmp, *buffer, ft_strlen(*buffer));
			*buffer = tmp;
			function_free((void **)&to_free,1);
		}
	}
}
int	pos_special_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (i);
		i++;
	}
	return (-1);
}
// int	pos_special_char(char c)
// {
// 		if (ft_isalnum(c) == 0 && c != '_') 
// 			return (1);
// 	return (-1);
// }

// void expand_words(char **str,char **result,)
// {
// 	int i=0;
// 	int start;
// 	char *key;

// 		if(str[i]=='$')
// 			{
// 				start=i;
// 				i++;
// 				while(str[i]!='$' && pos_special_char(str[i] ==-1))
// 					i++;
// 			}
// 			//else / =
// 		key=ft_substr(*str,start+1,i);
// 		if(key)
// 			char *value=get_env(key);
// 		if(value)
// 		{
// 			*result=ft_strdup(value);
// 		}
// 		else
// 			result=ft_strdup("");
// 		*str=ft_strdup(&*str[i]);
		
// }
// void expand(char**token)
// {
// 	int i=0;
// 	int pos_dollar;
// 	char **result;
// 	if(token)
// 	{
// 		pos_dollar=searching_for_char(*token,'$');
//  		if(pos_dollar!=-1)
//  		{
// 			*result=ft_substr(*token,0,pos_dollar);
// 			printf("result%s\n",result);
// 			*token=ft_substr(*token,pos_dollar,ft_strlen(*token) - pos_dollar);
// 		}
// 		while(str[i])
// 		{
// 			str=expand_words(&str,result);
			
// 		}
		
// 	}
// }

void	expand(char **token)
{
	char	*result;
	char	*path;
	char	*tmp_token;
	int		pos;
	char	*value;
	int		i;
	char	**split;
	char	*tmp_result;
	int  pos_dollar;

	path = NULL;
	i = 0;
	if (token)
	{
		pos_dollar=searching_for_char(*token,'$');
		result = ft_strdup("");
		if(pos_dollar!=-1)
		{
			result=ft_substr(*token,0,pos_dollar);
			// printf("%s\n",result);
			*token=ft_substr(*token,pos_dollar,ft_strlen(*token) - pos_dollar);
		}
		if ((*token)[0] == '$')
		{
			split = ft_split(*token, '$');
			while (split[i])
			{
				tmp_token = split[i];
				pos = pos_special_char(split[i]);

				if (pos != -1 && ft_strcmp(split[i],"?"))
				{
					*token = ft_substr(split[i], 0, pos);
					path = ft_strdup(&tmp_token[pos]);
				}
				else
					*token = split[i];
				if(!ft_strcmp(split[i],"?"))
					*token=split[i];
				value = get_env(*token);
				i++;
				if (value)
				{
					if (path)
					{
						tmp_result = ft_strjoin(value, path);
						result = ft_strjoin(result, tmp_result);
						path = NULL;
					}
					else
						result = ft_strjoin(result, value);
				}
				else if (!value)
				{	if(path)
							result = ft_strjoin(result, path);
					else
						result=ft_strjoin(result,ft_strdup("$"));
				}


			}
			*token = result;
		}
	}
}
int	get_char_position(char *buffer, char c)
{
	int	i;

	i = 0;
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] == c)
				return (i);
			i++;
		}
	}
	return (0);
}

int	len_str_to_expand(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			count++;
		i++;
	}
	return (count + 1);
}

char	*expand_with_quote(t_token *token)
{
	int		i;
	int		is_s_d_qoute;
	char	*tmp;
	char	*to_expand;
	char	*before_dollar;
	char	*after_dollar;

	is_s_d_qoute = -1;
	i = 0;
	tmp = NULL;
	is_s_d_qoute = 0;
	to_expand = NULL;
	before_dollar = NULL;
	after_dollar = NULL;

	if (token && ft_strchr(token->value, '$'))
	{
		if (token->value[0] == '"')
			is_s_d_qoute = 2;
		else if (token->value[0] == '\'')
			is_s_d_qoute = 1;
		if (is_s_d_qoute != -1)
		{
			remove_s_d_qoute(&token->value);
			if (is_s_d_qoute == 2)
			{
				tmp = token->value;
				while (tmp[i] && tmp[i] != '$')
					i++;
				before_dollar = ft_substr(token->value, 0, i);
				to_expand = ft_substr(token->value,
				get_char_position(token->value, '$'),
				ft_strlen(token->value) - i);
				expand(&to_expand);
				before_dollar = ft_strjoin(before_dollar, to_expand);
				return (before_dollar);
			}
			else
				return (token->value);
		}
		else
		{
			expand(&token->value);
		}
	}
	else
	{
		remove_s_d_qoute(&token->value);
	}

	return (token->value);
}

void	check_tild(t_token **token_cmd)
{
	char	*value;
	 char	*to_free;

	if (*token_cmd)
	{
		if ((*token_cmd)->value[0] == '~')
		{
			if ((*token_cmd)->value[1] == '\0')
				(*token_cmd)->value = HOME;
			if ((*token_cmd)->value[1] == ' ' || (*token_cmd)->value[1] == '/')
			{
				to_free = (*token_cmd)->value;
				value = ft_strdup(&((*token_cmd))->value[1]);
				(*token_cmd)->value = ft_strjoin(HOME, value);
				function_free((void**)&value, 1);
				function_free((void**)&to_free, 1);
			}
		}
	}
}

t_token 	*cmd_args_file(t_token *token_cmd, char **symb_file)
{
	int			flag;
	char		*result;
	char		*prev_str;
	t_token 	*cmd_arg;
	t_token 	*symb_fl;
	t_token 	*prev;
	t_token		*tmp;
	char		*to_free;

	flag = -1;
	cmd_arg = NULL;
	symb_fl = NULL;
	if (token_cmd)
	{
		while (token_cmd)
		{
			// red
			if (token_cmd->type == 0 || token_cmd->type == 1)
			{
				ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
						token_cmd->type));
				prev = token_cmd;
				token_cmd = token_cmd->next;
				if (token_cmd && token_cmd->type == prev->type)
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
							token_cmd->type));
					token_cmd = token_cmd->next;
				}
				while (token_cmd && token_cmd->type == 4)
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
							token_cmd->type));
					token_cmd = token_cmd->next;
				}
				while (token_cmd && (token_cmd->type == 3|| token_cmd->type == 7))
				{
					check_tild(&token_cmd);
					prev_str = ft_strdup(token_cmd->value);
					expand(&token_cmd->value);
					if (token_cmd->value[0]=='\0')
						token_cmd->value = prev_str;
					expand_with_quote(token_cmd);
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
							token_cmd->type));
					token_cmd = token_cmd->next;
				}
				flag = 0;
			}
			else if (token_cmd && token_cmd->type == 4)
			{
				while (token_cmd && token_cmd->type == 4)
				{
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value,
							token_cmd->type));
					token_cmd = token_cmd->next;
				}
			}
			else if (token_cmd && token_cmd->type == 3)
			{
				tmp = token_cmd;
				result = ft_strdup("");

				while (tmp && (tmp->type == 3 || tmp->type == 5 || tmp->type == 6))
				{
					//  leak
					to_free = result;
					result = ft_strjoin(result, expand_with_quote(tmp));
					function_free((void**)&to_free, 1);

					prev = tmp;
					tmp = tmp->next;
				}


					token_cmd = prev;
					function_free((void**)&token_cmd->value , 1);
					token_cmd->value = ft_strdup(result);

					function_free((void**)&result , 1);
				check_tild(&token_cmd);
				// expand(&token_cmd->value);
				remove_s_d_qoute(&token_cmd->value);
				ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value,
						token_cmd->type));
				token_cmd = token_cmd->next;
				flag = 1;

			}
			else if (token_cmd)
			{
				if (token_cmd && (token_cmd->type == 5 || token_cmd->type == 6))
				{
					tmp = token_cmd;
					//  leak
					result = ft_strdup("");
					while (tmp && (tmp->type == 5 || tmp->type == 6))
					{
						to_free = result;
						result = ft_strjoin(result, expand_with_quote(tmp));
						function_free((void**)&to_free, 1);
						prev = tmp;
						tmp = tmp->next;
					}
					token_cmd = prev;
					token_cmd->value = result;
				}
				else
					expand(&token_cmd->value);

				if (flag == 0)
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value,
							token_cmd->type));
				else if (flag == 1 || flag == -1)
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value,
							token_cmd->type));
				token_cmd = token_cmd->next;
			}
		}

		*symb_file = tokens_cmd_to_string(symb_fl);
	}
	return (cmd_arg);
}

//ls 15

t_command	*insert_one_cmd(char **cmd_args, char *symb_file)
{
	int			i;
	char		*to_free;
	char		*file;
	t_command	*new;
	t_list		*lst_redir;

	i = 0;
	new = malloc(sizeof(t_command));
	lst_redir = NULL;
	if (cmd_args && *cmd_args)
	{
		new->args = copy_of_tab(cmd_args);
		new->cmd = ft_strdup(new->args[0]);
	}
	else
	{
		new->args = malloc(sizeof(char *));
		new->args[0] = ft_strdup("");
		new->cmd = ft_strdup("");
	}
	while (symb_file && symb_file[i])
	{
		new->redir_in_out = malloc(sizeof(t_list));
		if (new->redir_in_out)
		{
			if (symb_file[i] == '>')
			{
				if (symb_file[i + 1] == '>')
				{
					new->redir_in_out->content = init_red(2);
					i += 2;
				}
				else if (symb_file[i++] == '>')
					new->redir_in_out->content = init_red(3);
			}
			else if (symb_file[i] == '<')
			{
				if (symb_file[i + 1] == '<')
				{
					new->redir_in_out->content = init_red(0);
					i += 2;
				}
				else if (symb_file[i++] == '<')
					new->redir_in_out->content = init_red(1);
			}
			file = ft_strdup("");
			while (symb_file[i] && symb_file[i] == ' ')
				i++;
			while (symb_file[i] && symb_file[i] != ' ' && symb_file[i] != '<'
				&& symb_file[i] != '>')
			{
				to_free = file;
				file = ft_strjoin(file, char_to_string(symb_file[i]));
				//function_free((void**)&to_free, 1);
				i++;
			}
			((t_red *)new->redir_in_out->content)->file_name = file;
			ft_lstadd_back(&lst_redir, ft_lstnew(new->redir_in_out->content));
		}
	}
	new->redir_in_out = lst_redir;
	return (new);
}

t_list	*store_one_cmd(t_token **tokens, char *symb)
{
	char		**tab;
	char		*symb_file;
	t_list		*lst;
	t_token 	*cmd_arg;
	t_token 	*tokens_cmd;
	t_token		*tmp_tokens;
	t_token *to_free;

	lst = NULL;
	tokens_cmd = NULL;
	tmp_tokens = *tokens;
	if (tmp_tokens && symb)
	{

		tokens_cmd = tokens_of_one_command(&tmp_tokens);
		while (tokens_cmd)
		{
			cmd_arg = cmd_args_file(tokens_cmd, &symb_file);
			// while(1);
			tab = token_cmd_to_args(cmd_arg);
			ft_lstadd_back(&lst, ft_lstnew(insert_one_cmd(tab, symb_file)));
			function_free((void **)tab, 3);
			function_free((void **)&cmd_arg, 2);
			function_free((void **)&symb_file, 1);

			to_free=tokens_cmd;
			tokens_cmd = tokens_of_one_command(&tmp_tokens);
			function_free((void**)&to_free, 2);
		}



	}
	return (lst);
}

char	*remove_char_from_str(char *buffer, char c)
{
	int		i;
	char	*str;
	char 	*to_free;

	i = 0;
	str = ft_strdup("");
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] != c)
			{
				to_free = str;
				str = ft_strjoin(str, char_to_string(buffer[i]));
				function_free((void**)&str, 1);
			}
			i++;
		}
	}
	return (str);
}

// free lexer types symb token
t_list	*parser(char *line)
{
	int 		flg_err=0;
	char		*symb;
	char		*types;
	t_list		*lst;
	t_lexer		*lexer;
	t_token 	*token;


	lexer = init_lexer(line);
	symb = ft_strdup("<>");
	types = ft_strdup("<>| '\"");
	token = get_all_tokens(lexer, types);

	function_free((void **)&lexer, 0);
	function_free((void **)&types, 1);

	check_parsing_error(token, &flg_err);
	// if(flg_err==1)
	// {
	// 	function_free((void **)&symb, 1);
	// 	function_free((void **)&token, 2);
	// 	add_node(&(g_data.env_vars), "?", ft_itoa(g_data.status_code), NULL);
	// 	return NULL;
	// }
	lst = store_one_cmd(&token, symb);

	function_free((void **)&symb, 1);
	 function_free((void **)&token, 2);

	herdoc(lst);//16
	return (lst);
}
