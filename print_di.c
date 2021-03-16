/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:44:47 by heeyang           #+#    #+#             */
/*   Updated: 2021/03/16 13:45:32 by heeyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	put_space_minus(t_data *data, char **str, int len)
{
	len = (data->prec > len) ? data->prec : len;
	if (len >= data->width)
	{
		if (data->idx_di == 2)
			*str = ft_strjoin("-", *str);
		else
			*str = ft_strjoin(" ", *str);
		data->num_return++;
	}
	else if (len < data->width && data->idx_di == 2)
		(*str)[0] = '-';
}

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

static void	di_base(t_data *data, long long di, char **str, int len)
{
	int		i;
	char	*base_di;

	if (di < 0)
		di *= -1;
	base_di = "0123456789";
	i = 0;
	while (len + i < data->prec)
		(*str)[i++] = '0';
	if (i != 0)
	{
		data->num_return += (data->prec - len);
		len = data->prec;
	}
	(*str)[len] = '\0';
	if (di == 0 && data->prec != 0)
		(*str)[len - 1] = '0';
	while (di)
	{
		(*str)[--len] = base_di[di % 10];
		di /= 10;
	}
	if (data->idx_di == 1)
		(*str) = ft_strjoin("-", (*str));
}

static int	len_di(t_data *data, long long di)
{
	int	i;

	if (di == 0 && data->prec != 0)
		return (1);
	i = 0;
	while (di)
	{
		di /= 10;
		i++;
	}
	return (i);
}

void		print_di(t_data *data)
{
	int		di;
	char	*str;
	int		len;

	di = (long long)va_arg(data->ap, int);
	len = len_di(data, di);
	if (di < 0 && data->zero == 0)
	{
		data->idx_di = 1;
		data->num_return++;
	}
	else if (di < 0 && data->zero == 1)
		data->idx_di = 2;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return ;
	di_base(data, di, &str, len);
	str = put_width(data, str, 0, 0);
	if (data->idx_di == 2 || data->idx_di == 3)
		put_space_minus(data, &str, len);
	ft_putstr_fd(str, 1);
	data->num_return += len;
	free(str);
}
