/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 04:18:29 by marvin            #+#    #+#             */
/*   Updated: 2025/01/27 04:18:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int	ft_atoi_base(const char *str, const char *base)
{
    int		i;
    int		sign;
    int		nb;
    int		base_len;

    i = 0;
    sign = 1;
    nb = 0;
    base_len = ft_strlen(base);
    while (ft_isspace(str[i]))
        i++;
    if (str[i] == '-' || str[i] == '+')
        if (str[i++] == '-')
            sign = -1;
    while (ft_strchr(base, str[i]))
    {
        nb = nb * base_len + (ft_strchr(base, str[i]) - base);
        i++;
    }
    return (nb * sign);
}
