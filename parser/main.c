/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:26:25 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/10 19:17:36 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include "cmd.h"
#include "../minishell.h"


t_red	*init_red(int flg)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	red->file_name = NULL;
	red->flag = flg;
	return (red);
}

t_list *init_lst()
{
	t_list		*lst;

	lst = malloc(sizeof(t_list));
	lst->content = NULL;
	lst->next = NULL;
	return (lst);
}

void remove_s_d_qoute(char **buffer)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (buffer)
	{
		if ((*buffer)[0] == '"' || (*buffer)[0] == '\'')
		{
			(*buffer)++;
			ft_strlcpy(tmp, *buffer, ft_strlen(*buffer));
			*buffer = tmp;
		}
	}
}

void expand(char **token)
{
	char	*result;

	result = NULL;
	if (token)
	{
		if ((*token)[0] == '$')
		{
			result = get_env(&((*token)[1]));
			if (result)
				(*token) = result;
		}
	}
}

int get_char_position(char *buffer, char c)
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
		if (ft_isalnum(str[i]))
			count++;
		i++;
	}
	return (count + 1);
}

char *expand_with_quote(token_t *token)
{
	int		i;
	int		is_s_d_qoute;
	char	*tmp;
	char	*to_expand;
	char	*before_dollar;
	char	*after_dollar;

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
			if (is_s_d_qoute == 2)
			{	// before dollar
				remove_s_d_qoute(&token->value);
				tmp = token->value;
				while (tmp[i] && tmp[i] != '$')
					i++;
				before_dollar = ft_substr(token->value, 0, i);
				to_expand = ft_substr(token->value, get_char_position(token->value, '$'), len_str_to_expand(token->value));
				expand(&to_expand);
				before_dollar = ft_strjoin(before_dollar, to_expand);
				after_dollar = ft_substr(tmp, i + len_str_to_expand(token->value), ft_strlen(tmp) - i + len_str_to_expand(token->value));
				after_dollar = ft_strjoin(before_dollar, after_dollar);
				return (after_dollar);
			}
		}
	}
	return (NULL);
}

void cmd_args_file(token_t *token_cmd, char **cmd_args, char **symb_file)
{
	int		flag;
	token_t	*cmd_arg;
	token_t	*symb_fl;
	token_t	*prev;

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
				ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
				prev = token_cmd;
				token_cmd = token_cmd->next;
				if (token_cmd && token_cmd->type == prev->type)
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				while (token_cmd && token_cmd->type == 4)
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				while (token_cmd && token_cmd->type == 3)
				{//
					expand(&token_cmd->value);
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				flag = 0;
			}
			else if (token_cmd && token_cmd->type == 4)
			{
				while (token_cmd && token_cmd->type == 4)
				{
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
			}
			else if (token_cmd && token_cmd->type == 3)
			{//
				while (token_cmd && token_cmd->type == 3)
				{
					expand(&token_cmd->value);
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				flag = 1;
			}
			else if (token_cmd)
			{
				char	*result;
				while (token_cmd && (token_cmd->type == 5 || token_cmd->type == 6))
				{
					result = expand_with_quote(token_cmd);
					//$ + quote
					if (result)
					{
						token_cmd->value = result;
						break;
						//token_cmd->value = ft_strjoin(token_cmd->value, expand_with_quote(token_cmd));
					}
					else
					{
						remove_s_d_qoute(&token_cmd->value);
						printf("%s\n", token_cmd->value);
					}
					token_cmd = token_cmd->next;
				}
				expand(&(token_cmd)->value);
				if (flag == 0 )
				{
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				else if (flag == 1|| flag == -1)
				{
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}

					//printf(" ss  %s\n",token_cmd->value);


			}
		}
		*cmd_args = tokens_cmd_to_string(cmd_arg);
		*symb_file = tokens_cmd_to_string(symb_fl);
		printf("   %s\n",*cmd_args);
		printf("   %s\n",*symb_file);
	}
}

t_command *insert_one_cmd(char *cmd_args, char *symb_file)
{
	int			i;
	int			flag;
	char		*file;
	t_command	*new;
	t_list		*lst_redir_in;
	t_list		*lst_redir_out;

	i = 0;
	flag = -1;
	new = malloc(sizeof(t_command));
	new->redir_out = malloc(sizeof(t_list));
	new->redir_in = malloc(sizeof(t_list));
	lst_redir_in = NULL;
	lst_redir_out = NULL;
	if (cmd_args)
	{
		new->args = ft_split(cmd_args, ' ');
		new->cmd = ft_strdup(new->args[0]);
	}
	else
	{
		new->args[0] = NULL;
		new->cmd = NULL;
	}
	while (symb_file && symb_file[i])
	{
		if (symb_file[i] == '>')
		{
			flag = 0;
			if (symb_file[i + 1] == '>')
			{
				new->redir_out->content = init_red(0);
				i += 2;
			}
			else if (symb_file[i] == '>')
			{
				new->redir_out->content = init_red(1);
				i++;
			}
		}
		else if (symb_file[i] == '<')
		{
			flag = 1;
			if (symb_file[i + 1] == '<')
			{
				new->redir_in->content = init_red(0);
				i += 2;
			}
			else if (symb_file[i] == '<')
			{
				new->redir_in->content = init_red(1);
				i++;
			}
		}
		file = ft_strdup("");
		while (symb_file[i] && symb_file[i] == ' ')
			i++;
		while (symb_file[i] && symb_file[i] != ' ' && symb_file[i] != '<' && symb_file[i] != '>' )
		{
			file = ft_strjoin(file, char_to_string(symb_file[i]));
			i++;
		}
		if (flag == 0)
		{
			((t_red *)new->redir_out->content)->file_name = file;
			ft_lstadd_back(&lst_redir_out,ft_lstnew(new->redir_out->content));
		}
		else if (flag == 1)
		{
			((t_red *)new->redir_in->content)->file_name = file;
			ft_lstadd_back(&lst_redir_in, ft_lstnew(new->redir_in->content));
		}
		flag = -1;
	}
	new->redir_in =  lst_redir_in;
	new->redir_out = lst_redir_out;
	return (new);
}

t_list *store_one_cmd(token_t **tokens, char *symb)
{
	t_list		*lst;
	char		*symb_file;
	char		*cmd_args;
	token_t		*tokens_cmd;

	lst = NULL;
	tokens_cmd = NULL;
	if (tokens && *tokens && symb)
	{
		tokens_cmd = tokens_of_one_command(tokens);
		while (tokens_cmd)
		{
			cmd_args_file(tokens_cmd, &cmd_args, &symb_file);
			ft_lstadd_back(&lst, ft_lstnew(insert_one_cmd(cmd_args, symb_file)));
			cmd_args = NULL;
			symb_file = NULL;
			tokens_cmd = tokens_of_one_command(tokens);
		}
	}
	// int i;	/// AFFICHAGE
	// while (lst && lst->content)
	// {
	// 	//	cmd
	// 	i = 0;
	// 	printf("cmd :%s\nargs :",((t_command *)(lst->content))->cmd);
	// 	// args
	// 	while (((t_command *)(lst->content))->args[i])
	// 	{
	// 		printf("\n\t %s \n",((t_command *)(lst->content))->args[i]);
	// 		i++;
	// 	}
	// 	printf("\n");
	// 	// in files
	// 	while (((t_red *)((t_command *)(lst->content))->redir_in) != NULL)
	// 	{
	// 		printf("redir_in : %s , flag :%d\n",((t_red *)((t_command *)(lst->content))->redir_in->content)->file_name
	// 			, ((t_red *)((t_command *)(lst->content))->redir_in->content)->flag);
	// 		((t_command *)(lst->content))->redir_in = ((t_command *)(lst->content))->redir_in->next;
	// 	}
	// 	// out files
	// 	while (((t_red *)((t_command *)(lst->content))->redir_out) != NULL)
	// 	{
	// 		printf("redir_out : %s , flag :%d\n",((t_red *)((t_command *)(lst->content))->redir_out->content)->file_name
	// 			, ((t_red *)((t_command *)(lst->content))->redir_out->content)->flag);
	// 		((t_command *)(lst->content))->redir_out = ((t_command *)(lst->content))->redir_out->next;
	// 	}
	// 	printf("\n------------------------------------------\n");
	// 	lst = lst->next;
	// }
	// exit(1);
	return (lst);
}

char	*remove_char_from_str(char *buffer, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] != c)
				str = ft_strjoin(str, char_to_string(buffer[i]));
			i++;
		}
	}
	return (str);
}

t_list	*parser(char *line, int *flg_err)
{
	lexer_t	*lexer;
	token_t	*token;
	char	*symb;
	char	*types;
	t_list	*lst;

	lexer = init_lexer(line);
	symb = malloc(3);
	types = malloc(9);
	symb = "<>";
	types = "<>| '\"$";
	token = get_all_tokens(lexer, types);
	check_parsing_error(token, flg_err);
	lst = store_one_cmd(&token, symb);
	herdoc(lst);
	exit(1);
	//printf("%d\n", g_data.status_code);
	return (lst);
}

