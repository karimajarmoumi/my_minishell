/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:37:23 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/03 22:55:06 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H


#include "token.h"
#include "cmd.h"
#include "../minishell.h"

int			count_token_cmd(token_t *token);

char		*get_one_command(token_t **token);


#endif