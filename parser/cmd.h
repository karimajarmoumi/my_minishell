/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:37:23 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/18 18:10:35 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include "token.h"
#include "cmd.h"
#include "../minishell.h"

int			count_token_cmd(t_token *token);
char		*get_one_command(t_token **token);

#endif