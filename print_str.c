/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 10:54:25 by heeyang           #+#    #+#             */
/*   Updated: 2021/03/12 06:28:33 by heeyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*put_width(t_data *data, char *temp, int i)
{
	char	*str;
	int		j;

	if ((size_t)data->width <= ft_strlen(temp))
		return (temp);
	if (!(str = (char *)malloc(sizeof(char) * (data->width + 1))))
		return (0);
	j = 0;
	if (data->minus == 0)
	{
		while ((size_t)i < (size_t)data->width - ft_strlen(temp))
			str[i++] = ' ';
		while (temp[j] != '\0')
			str[i++] = temp[j++];
	}
	else
	{
		while (temp[j] != '\0')
			str[i++] = temp[j++];
		while (i < data->width)
			str[i++] = ' ';
	}
	str[i] = '\0';
	free(temp);
	return (str);
}

static char	*read_str(t_data *data, char *str)
{
	char	*temp;
	int		len;
	int		i;

	if (data->prec == -1 || (size_t)data->prec > ft_strlen(str))
		len = ft_strlen(str);
	else
		len = data->prec;
	if (!(temp = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void		print_str(t_data *data)
{
	char	*str;
	char	*temp;

	str = va_arg(data->ap, char *);
	if (str == NULL)
		str = "(null)";
	temp = read_str(data, str);
	str = put_width(data, temp, 0);
	ft_putstr_fd(str, 1);
	data->num_return += ft_strlen(str);
	free(str);
}
