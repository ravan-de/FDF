#include "mlx.h"
#include "libft.h"
#include "fdf.h"

int     abs(int nb)
{
    if (nb < 0)
        nb *= -1;
    return (nb);
}

void    ft_line_steep(int dx, int dy, t_mlx *data)
{
    int x;
    int y;
    int D;
    
    x = 0;
    y = 0;
    D = 2 * dx - abs(dy);
    while (x <= dx && dx != 0)
    {
        mlx_pixel_put(data->con, data->wind, data->x_start + x, data->y_start + y, data->color);
        if (dy < 0)
            y--;
        else
            y++;
        if (D < 0)
            D += 2 * dx;
        else
        {
            D += 2 * dx - 2 * abs(dy);
            x++;
        }
    }
}

void    ft_line(int dx, int dy, t_mlx *data)
{
    int     x;
    int     y;
    int     D;
    
    x = 0;
    y = 0;
    D = 2 * abs(dy) - dx;
    while (x <= dx)
    {
        mlx_pixel_put(data->con, data->wind, data->x_start + x, data->y_start + y, data->color);
        x++;
        if (D < 0)
            D += 2 * abs(dy);
        else
        {
            D += 2 * abs(dy) - 2 * dx;
            if (dy < 0)
                y--;
            else
                y++;
        }
    }
}

void    ft_line_vert(int dy, t_mlx *data)
{
    int y;

    y = 0;
    while (y != dy)
    {
        mlx_pixel_put(data->con, data->wind, data->x_start, data->y_start + y, data->color);        
        if (dy < 0)
            y--;
        else
            y++;
    }
}

void    ft_draw(t_mlx *data)
{
    int dx;
    int dy;
    int swap;

    swap = 0;
    dx = data->x_end - data->x_start;
    if (dx < 0)
    {
        swap = 1;
        ft_putstr("swap");
        ft_swap(&data->x_end, &data->x_start);
        ft_swap(&data->y_end, &data->y_start);
    }
    dx = data->x_end - data->x_start;
    dy = data->y_end - data->y_start;
    if (dx == 0)
        ft_line_vert(dy, data);
    else if (dx > abs(dy))
        ft_line(dx, dy, data);
    else
        ft_line_steep(dx, dy, data);
    if (swap == 1)
    {
        ft_swap(&data->x_end, &data->x_start);
        ft_swap(&data->y_end, &data->y_start);
    }
}