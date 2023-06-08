/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:26:25 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/08 22:01:11 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include "cmd.h"
#include "../minishell.h"

token_t	*ft_lstlast_token(token_t *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_token(token_t **lst, token_t *new)
{
	token_t	*last_node;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			last_node = ft_lstlast_token(*lst);
			last_node->next = new;
		}
	}
}

token_t *copy_of_list(token_t *original, int size)
{
	int		i;
	token_t *copy;

	i = 0;
	copy = NULL;
	if (original)
	{
		while (original && i < size)
		{
			ft_lstadd_back_token(&copy, init_token(original->value, original->type));
			original = original->next;
			i++;
		}
	}
	return (copy);
}

int	number_of_tokens_before_pipe(token_t *token)
{
	int i;

	i = 0;
	if (token)
	{
		while (token && token->value[0] != '|')
		{
			i++;
			token = token->next;
		}
	}
	return (i);
}

token_t *tokens_of_one_command(token_t **token)
{
	int		i;
	int		count_token;
	token_t *tokens_cmd;

	i = 0;
	tokens_cmd = NULL;

	if (token && *token)
	{
		count_token = number_of_tokens_before_pipe(*token);
		tokens_cmd = copy_of_list(*token ,count_token);
		while (*token  && i <= count_token)
		{
			*token = (*token)->next;
			i++;
		}
	}
	return (tokens_cmd);
}

char	*tokens_cmd_to_string(token_t *token)
{
	char	*buffer;

	buffer = ft_strdup("");
	if (token)
	{
		while (token)
		{
			buffer = ft_strjoin(buffer, token->value);
			token = token->next;
		}
		buffer = ft_strjoin(buffer, "\0");
	}
	return (buffer);
}

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
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				flag = 1;
			}
			else if (token_cmd)
			{
				if (flag == 0 )
				{
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&symb_fl, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
				else if (flag == 1|| flag == -1)
				{//
					remove_s_d_qoute(&token_cmd->value);
					ft_lstadd_back_token(&cmd_arg, init_token(token_cmd->value, token_cmd->type));
					token_cmd = token_cmd->next;
				}
			}
		}
		*cmd_args = tokens_cmd_to_string(cmd_arg);
		*symb_file = tokens_cmd_to_string(symb_fl);
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
	// printf("cc\n");
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

int pipe_error(token_t *tokens, token_t *prev)
{
	char	*buffer;

	buffer = NULL;
	if (tokens)
	{
		tokens = tokens->next;
		if (!prev)
		{
			buffer =  ft_strdup("syntax error near unexpected token `|");
			if (tokens && tokens->value[0] == '|')
			{
				buffer = ft_strjoin(buffer, "|");
				tokens = tokens->next;
			}
			buffer = ft_strjoin(buffer, "'");
			print_cmd_error(NULL, NULL, buffer, 258);
			return (1);
		}
		else
		{
			while (tokens && tokens->type == 4)
				tokens = tokens->next;
			if (!tokens || (tokens && tokens->type == 2))
			{
				print_cmd_error(NULL, NULL, ft_strdup("syntax error near unexpected token `|'"), 258);
				return (1);
			}
		}
	}
	return (0);
}



// int qoute_error(token_t *tokens)
// {
// 	char	to_remove;
// 	char	*buffer;

// 	buffer = ft_strdup("");
// 	to_remove = '\0';
// 	if (tokens)
// 	{
// 		buffer = ft_strjoin(buffer, tokens->value);
// 		tokens = tokens->next;
// 		to_remove = tokens->value[0];
// 		while (tokens && tokens->type != 4)
// 		{
// 			if (tokens->type == 5 || tokens->type == 6)
// 				buffer = ft_strjoin(buffer, tokens->value);
// 			else if (tokens->type == 7 && tokens->next->type != 4)
// 				buffer = ft_strjoin(buffer, char_to_string(tokens->value[0]));
// 			tokens = tokens->next;
// 		}

// 		print_cmd_error(buffer, NULL, "command not found", 127);
// 		return (1);
// 	}
// 	return (0);
// }

int qoute_error(token_t *token)
{
	if (token)
	{
		if (ft_strlen(token->value) == 1)
		{
			print_cmd_error(NULL, NULL, "syntax error", 1);
			return (1);
		}
		else if (token->value[ft_strlen(token->value) - 1] != token->value[0])
		{
			print_cmd_error(NULL, NULL, "syntax error", 1);
			return (1);
		}
	}
	return (0);
}

int redir_in_error(token_t *token)
{
	int		i;
	int		flag;
	char	*buffer;

	i = 0;
	flag = -1;
	buffer = ft_strdup("");
	if (token)
	{
		token = token->next;
		if (token && (token->type == 0))
		{
			token = token->next;
			flag = 0;
		}
		if (token && (token->type == 0))
			token = token->next;
		while (token && token->type == 4)
			token = token->next;
		if (!token || (token && flag && token->type == 1))
		{
			print_cmd_error(NULL, NULL, "syntax error near unexpected token `newline'", 258);
			return (1);
		}
		else if (token->type == 0 || token->type == 1 || token->type == 2)
		{
			buffer = "syntax error near unexpected token `";
			while (token && ((token->type == 0 && i < 3) || (token->type == 1 && i < 2)))
			{
				buffer = ft_strjoin(buffer, token->value);
				token = token->next;
				i++;
			}
			if (token && token->type == 2)
				buffer = ft_strjoin(buffer, token->value);
			print_cmd_error(NULL, NULL, ft_strjoin(buffer, "'"), 258);
			return (1);
		}
	}
	return (0);
}

int redir_out_error(token_t *token)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = ft_strdup("");
	if (token)
	{
		token = token->next;
		if (token && token->type == 2)
		{
			token = token->next;
			while (token && token->type == 4)
				token = token->next;
			if (!token)
			{
				print_cmd_error(NULL, NULL, "syntax error near unexpected token `newline'", 258);
				return (1);
			}
			return (0);
		}
		if (token && token->type == 1)
			token = token->next;
		while (token && token->type == 4)
			token = token->next;
		if (token && (token->type == 0 || token->type == 1 || token->type == 2))
		{
			buffer = "syntax error near unexpected token `";
			while (token && ((i < 2 && (token->type == 2 || token->type == 1))
				|| (i < 3 && token->type == 0)))
			{
				buffer = ft_strjoin(buffer, token->value);
				token = token->next;
				i++;
			}
			print_cmd_error(NULL, NULL, ft_strjoin(buffer, "'"), 258);
			return (1);
		}
		if (!token)
		{
			print_cmd_error(NULL, NULL, "syntax error near unexpected token `newline'", 258);
			return (1);
		}
	}
	return (0);
}

int redir_error(token_t *token, int type)
{
	if (token)
	{
		if (type == 0 && redir_in_error(token))
			return (1);
		else if (type == 1 && redir_out_error(token))
			return (1);
	}
	return (0);
}

void	check_parsing_error(token_t *tokens, int *flg_err)
{
	token_t *prev;

	prev = NULL;
	if (tokens)
	{
		while (tokens)
		{
			if (tokens->type == 3)
				prev = tokens;
			else if (tokens->value[0] == '|')
			{
				*flg_err = pipe_error(tokens, prev);
				if (*flg_err)
					break;
			}
			else if (tokens->value[0] == '<')
			{
				*flg_err = redir_error(tokens , 0);
				if (*flg_err)
					break;
			}
			else if (tokens->value[0] == '>')
			{
				*flg_err = redir_error(tokens , 1);
				if (*flg_err)
					break;
			}
			else if (tokens->type == 5 || tokens->type == 6)
			{
				*flg_err = qoute_error(tokens);
				if (*flg_err)
					break;
			}
			// if (tokens->next && (tokens->next->type == 5 || tokens->next->type == 6))
			// 	qoute_error(tokens);
			tokens = tokens->next;
		}

	}
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
	//lst = remove_qoute(lst);
	return (lst);
}
