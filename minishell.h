/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:31:33 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/20 19:27:53 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "parser/token.h"
# include <ctype.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define PERPOL " \033[0;35m"
# define TABLE_SIZE 1024
# define CYAN " \033[0;36m"
# define HOME "/Users/kjarmoum"
# include "parser/cmd.h"
# include "parser/lexer.h"
# include "parser/token.h"



typedef struct t_list
{
	void			*content;
	struct t_list	*next;

}					t_list;

typedef struct t_red
{
	void			*file_name;
	int				flag;
	int				fd_herdoc;
}					t_red;

typedef struct s_command
{
	char			*cmd;
	char			**args;
	int				flg;
	t_list			*redir_in_out;
}					t_command;

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;

}					t_node;

typedef struct s_data
{
	t_node			*env_vars;
	int				status_code;
	int				count_envs;
	int				isChild;
	char            *current_dir;
	struct termios	new_term;
	struct termios	old_term;

}					t_data;

t_data				g_data;

char				**token_cmd_to_args(t_token *token_cmd);
t_command			*read_cmds(t_command *data, char **av, int ac);
int					ft_lstsize_token(t_token *lst);
char				*ft_substr(char const *s, unsigned int start, size_t len);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
void				executer(t_list *command);
t_list				*init_commands(void);
int					ft_atoi(const char *str,int *flag);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content);
int					ft_strchr_str(char *str, char *c);
int					print_cmd_error(char *cmd, char *args, char *msg_err,
						int status_code);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*get_actual_path(char *cmd);
void				free_double_ptr(char **ptr);
void				initilizer(char **envs);
void				init_envs(char **envs);
int					ft_env(int fd);
int					searching_for_char(char *str, char c);
void				add_node(t_node **head, char *key, char *value,
						t_node *parent);
void				inorder_traversal(t_node *head, int fd);
void				remove_node(t_node **head, char *key);
void				free_node(t_node **node);
void				ft_free(void *ptr);
// void				ft_free_test(void **ptr);
int					ft_pwd(char *cmd, int fd);
int					ft_cd(t_command *command);
int					ft_echo(t_command *command, int fd);
int					ft_export(t_command *command, int fd);
int					ft_unset(t_command *command);
int					is_bultin(char *cmd);
int					execute_bultin(t_command *command, int fd);
t_node				*get_node(t_node *head, char *key);
char				*get_env(char *key);
char				*ft_itoa(int n);
int					is_valid_key(char *key);
int					ft_exit(t_command *command);
int					is_num(char *str);
char				**store_envs(t_node *head, char **tmp, int *i);
void				prompt(int sig);
void				signals_for_child(void);
void				signals_for_parent(void);
t_node				*get_most_left(t_node *node);
char				*ft_strchr(const char *s, int c);
t_command			*store_one_command(t_token **token);
char				**convert_tree_to_array(void);
t_token 				*cmd_args_file(t_token *token_cmd, char **symb_file);
t_command			*insert_one_cmd(char **cmd_args, char *symb_file);
t_red				*init_red(int flg);
t_token 			*tokens_of_one_command(t_token **token);
char				*tokens_cmd_to_string(t_token *token);

void				ft_bzero(void *s, size_t n);
char				*ft_strchr(const char *s, int c);
t_list				*parser(char *line);
t_command			*store_one_command(t_token **token);
char				**convert_tree_to_array(void);
int					get_inputfile_fd(t_list *lst_redir, int *last_fd,
						int *tmp_read_fd);
int					get_outfile_fd(t_list *lst_redir, int *fd,
						int *tmp_write_fd);
void				duplicate_fds(t_list *tmp, int last_fd, int *fds,
						int tmp_fds);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				exec_herdoc(char *del, int fd);
void				herdoc(t_list *command_lst);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
t_token 				*tokens_of_one_command(t_token **token);
char				*tokens_cmd_to_string(t_token *token);
int					number_of_tokens_before_pipe(t_token *token);
t_token 				*copy_of_list(t_token *original, int size);
void				expand(char **token);
void				exec_herdoc(char *del, int fd);
void				herdoc(t_list *command_lst);
void check_parsing_error(t_token *tokens, int *flg_err);
int					redir_out_error(t_token *token);
int					redir_error(t_token *token, int type);
int					redir_in_error(t_token *token);
int					qoute_error(t_token *token);
int					pipe_error(t_token *tokens, t_token *prev);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_strcmp(char *s1, char *s2);
char				**copy_of_tab(char **str);
int					ft_isalnum(int c);
void				free_red(t_list *redir_list);
void				free_commands(t_list *commands);
void				get_fds(t_list *lst_files, int *read_fd, int *write_fd);
void				my_free(char *value, char *key);
void				init_value(int *pos, int *flag, int *i, int *status);
int					check_err_export(char *arg,char *key, char *cmd);
char* get_working_dir();

void my_free(char *value,char *key);
void	init_value(int *pos, int *flag, int *i, int *status);
int	check_err(char *key, char *cmd, int *i);
void function_free(void **to_free, int type);
int	ft_free_test(void **ptr);
// t_token	*ft_lstlast_token(t_token *lst);
#endif
