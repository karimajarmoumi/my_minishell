// #include "../minishell.h"

// t_red *generatFile(char *file_name,int flag)
// {
// 	t_red *red= malloc(sizeof(t_red));
// 	red->file_name = ft_strdup(file_name);
// 	red->flag = flag;
// 	return (red);
// }

// t_command *generateCommand(char *cmd, char *args,
//		char *infile,char *outfile,int flag)
// {
// 	t_command	*command;
// 	command = calloc(sizeof(t_command),1);
// 	if(cmd)
// 		command->cmd = cmd;
// 	if(args)
// 		command->args = ft_split(args, ' ');
// 	if (infile)
// 		ft_lstadd_back(&(command->redir_in),ft_lstnew(generatFile(infile,flag)));
// 	if(outfile)
// 		ft_lstadd_back(&(command->redir_out),ft_lstnew(generatFile(outfile,flag)));
// 	return (command);
// }

// t_list	*init_commands()
// {
//  	t_list *commands = NULL;
// 	ft_lstadd_back(&commands,ft_lstnew(generateCommand(NULL,NULL,
//					NULL,"kawtar",0)));
// 	ft_lstadd_back(&commands,ft_lstnew(generateCommand(NULL,NULL,
//					NULL,"med",0)));

// 	return (commands);
// }