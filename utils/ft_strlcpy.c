/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:52:05 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/15 22:04:11 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}


char **copy_of_tab(char **str)
{

	int len=0;
	int i=0;
	char **dest;
	if(!str || !*str)
		return NULL;
	while(str[len])
		len++;
	dest=malloc(sizeof(char *) *(len +1));
	if(dest)
	{
		while(str[i])
		{
			dest[i]= ft_strdup(str[i]);
			i++;
		}
	}
	return dest;
}