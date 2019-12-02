/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_calc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ravan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/26 20:03:06 by ravan-de      #+#    #+#                 */
/*   Updated: 2019/04/01 19:28:15 by ravan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "printf.h"

void    nb_x_matrix(double nb, double **matrix)
{
    int row;
    int col;

    row = 0;
    while (row < 3)
    {
        col = 0;
        while (col < 3)
        {
            matrix[row][col] = nb * matrix[row][col];
            col++;
        }
        row++;
    }
}

double    *vect_x_matrix(double x, double y, double z, double **matrix)
{
    int     row;
    double  *resvect;

    resvect = malloc(sizeof(double) * 3);
    resvect[0] = 0;
    resvect[1] = 0;
    resvect[2] = 0;
    row = 0;
    while (row < 3)
    {
        resvect[row] += matrix[row][0] * x;
        resvect[row] += matrix[row][1] * y;
        resvect[row] += matrix[row][2] * z;
        row++;
    }
    return (resvect);
}



void    print_matrix(double **matrix)
{
    int row;
    int col;

    row = 0;
    while (row < 3)
    {
        col = 0;
        while (col < 3)
        {
            ft_printf("%.1f ", matrix[row][col]);
            col++;
        }
        ft_printf("\n");
        row++;
    }
}