/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 02:07:23 by heeyang           #+#    #+#             */
/*   Updated: 2021/03/15 03:26:31 by heeyang          ###   ########.fr       */
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
	data->num_return += (data->width - (int)ft_strlen(temp));
	str[i] = '\0';
	free(temp);
	return (str);
}

static void	ptr_base(t_data *data, unsigned long long ptr, char **str, int len)
{
	int		i;
	char	*base_ptr;

	base_ptr = "0123456789abcdef";
	(*str)[len] = '\0';
	if (ptr == 0 && data->prec != 0)
		(*str)[0] = '0';
	i = 1;
	while (ptr)
	{
		(*str)[len - i] = base_ptr[ptr % 16];
		ptr /= 16;
		i++;
	}
}

static int	len_ptr(t_data *data, unsigned long long ptr)
{
	int	i;

	if (ptr == 0 && data->prec != 0)
		return (1);
	i = 0;
	while (ptr)
	{
		ptr /= 16;
		i++;
	}
	return (i);
}

void		print_ptr(t_data *data)
{
	unsigned long long	ptr;
	char				*str;
	int					len;

	ptr = (unsigned long long)va_arg(data->ap, void *);
	len = len_ptr(data, ptr);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return ;
	ptr_base(data, ptr, &str, len);
	str = ft_strjoin("0x", str);
	str = put_width(data, str, 0, 0);
	ft_putstr_fd(str, 1);
	data->num_return += (len + 2);
	free(str);
}
