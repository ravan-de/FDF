/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ravan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 16:42:35 by ravan-de      #+#    #+#                 */
/*   Updated: 2019/04/04 18:17:09 by ravan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_swap(int *one, int *two)
{
    int temp;

    temp = *one;
    *one = *two;
    *two = temp;
}