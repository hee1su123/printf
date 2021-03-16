/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 03:38:09 by heeyang           #+#    #+#             */
/*   Updated: 2021/03/15 02:19:38 by heeyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*put_width(t_data *data, char *temp, int i, int j)
{
	char *str;

	if ((size_t)data->width <= ft_strlen(temp))
		return (temp);
	if (!(str = (char *)malloc(sizeof(char) * (data->width + 1))))
		return (0);
	if (data->minus == 0)
	{
		while ((size_t)i < (size_t)data->width - ft_strlen(temp))
			str[i++] = (data->zero == 1) ? '0' : ' ';
		while (temp[j] != '\0')
			str[i++] = temp[j++];
	}
	else
	{
		while (temp[j] != '\0')
			str[i++] = temp[j++];
		while (i < data->width)
			str[i++] = (data->zero == 1) ? '0' : ' ';
	}
	data->num_return += (data->width - (int)ft_strlen(temp));
	str[i] = '\0';
	free(temp);
	return (str);
}

static void	u_base(t_data *data, unsigned int u, char **str, int len)
{
	int		i;
	char	*base_u;

	base_u = "0123456789";
	i = 0;
	while (len + i < data->prec)
		(*str)[i++] = '0';
	if (i != 0)
	{
		data->num_return += (data->prec - len);
		len = data->prec;
	}
	(*str)[len] = '\0';
	if (u == 0 && data->prec != 0)
		(*str)[len - 1] = '0';
	while (u)
	{
		(*str)[--len] = base_u[u % 10];
		u /= 10;
	}
}

static int	len_u(t_data *data, unsigned int u)
{
	int	i;

	if (u == 0 && data->prec != 0)
		return (1);
	i = 0;
	while (u)
	{
		u /= 10;
		i++;
	}
	return (i);
}

void		print_u(t_data *data)
{
	unsigned int	u;
	char			*str;
	int				len;

	u = va_arg(data->ap, unsigned int);
	len = len_u(data, u);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return ;
	u_base(data, u, &str, len);
	str = put_width(data, str, 0, 0);
	ft_putstr_fd(str, 1);
	data->num_return += len;
	free(str);
}
