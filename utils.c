/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 08:28:07 by heeyang           #+#    #+#             */
/*   Updated: 2021/03/15 16:13:06 by heeyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_data(t_data *data)
{
	data->zero = 0;
	data->minus = 0;
	data->width = 0;
	data->prec = -1;
	data->spec = 0;
	data->idx_di = 0;
}

int		ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return (0);
	write(fd, &c, 1);
	return (1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0 || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == (char)c)
			return ((char *)(str + i));
		else
			i++;
	}
	if ((char)c == '\0')
		return ((char *)(str + i));
	return (0);
}
