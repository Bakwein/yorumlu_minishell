/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsozan <hsozan@42kocaeli.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:44:27 by hsozan            #+#    #+#             */
/*   Updated: 2023/02/19 13:44:27 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strpcpy(char *dst, char *src, int count)
{
	char	*ptr;
	char	*return_ptr;
	int		index;

	if (!src || !count)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(dst) + count + 1));
	return_ptr = ptr;
	index = -1;
	while (dst && *dst)
		*(ptr++) = *(dst++);
	while (++index < count && src && *src)
		*(ptr++) = *(src++);
	*ptr = 0;
	return (return_ptr);
}
