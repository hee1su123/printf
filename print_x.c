/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:45:59 by heeyang           #+#    #+#             */
/*   Updated: 2021/03/15 03:32:30 by heeyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*put_width(t_data *data, char *temp, int i, int j)
{
	char	*str;

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

static void	x_base(t_data *data, unsigned int x, char **str, int len)
{
	int		i;
	char	*base_x;
	char	*base_cx;

	base_x = "0123456789abcdef";
	base_cx = "0123456789ABCDEF";
	i = 0;
	while (len + i < data->prec)
		(*str)[i++] = '0';
	if (i != 0)
	{
		data->num_return += (data->prec - len);
		len = data->prec;
	}
	(*str)[len] = '\0';
	if (x == 0 && data->prec != 0)
		(*str)[len - 1] = '0';
	while (x)
	{
		if (data->spec == 'x')
			(*str)[--len] = base_x[x % 16];
		else
			(*str)[--len] = base_cx[x % 16];
		x /= 16;
	}
}

static int	len_x(t_data *data, unsigned int x)
{
	int	i;

	if (x == 0 && data->prec != 0)
		return (1);
	i = 0;
	while (x)
	{
		x /= 16;
		i++;
	}
	return (i);
}

void		print_x(t_data *data)
{
	unsigned int	x;
	char			*str;
	int				len;

	x = va_arg(data->ap, unsigned int);
	len = len_x(data, x);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return ;
	x_base(data, x, &str, len);
	str = put_width(data, str, 0, 0);
	ft_putstr_fd(str, 1);
	data->num_return += len;
	free(str);
}
