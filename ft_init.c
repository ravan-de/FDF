#include <stdlib.h>
#include "libft/includes/libft.h"
#include "libft/includes/mlx.h"
#include "fdf.h"
#include <stdio.h>

int     abs(int nb)
{
    if (nb < 0)
        nb *= -1;
    return (nb);
}

void    ft_line_steep(int dx, int dy, void *param)
{
    t_mlx   *data;
    int x;
    int y;
    int D;
    
    data = (t_mlx *)param;
    x = 0;
    y = 0;
    D = 2 * dx - abs(dy);
    while (x <= dx)
    {
        mlx_pixel_put(data->con, data->wind, x, 0.5 * SIZE_Y - y, 255);
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

void    ft_line(int dx, int dy, void *param)
{
    t_mlx   *data;
    int     x;
    int     y;
    int     D;
    
    data = (t_mlx *)param;
    x = 0;
    y = 0;
    D = 2 * abs(dy) - dx;
    while (x <= dx)
    {
        mlx_pixel_put(data->con, data->wind, x, 0.5 * SIZE_Y - y, 255);
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

int    ft_key_pressed(int keycode, void *param)
{
    static int x = 1000;
    static int y = -1;

    y *= 2;
    ft_putnbr(keycode);
    if (keycode == 53) //escape
        exit(0);
    if (keycode == 36) //enter
    {
        if (x > abs(y))
            ft_line(x, y, param);
        else
            ft_line_steep(x, y, param);
    }
    return (0);
}

int     ft_putimage(void *param)
{
    t_mlx   *data = (t_mlx *)param;
    mlx_put_image_to_window(data->con, data->wind, data->img, 10, 10);
    return (0);
}

void    ft_init(t_splitlst *lst)
{
    (void)lst;
    t_mlx   data;

    data.bpp = 0;
    data.line = 0;
    data.end = 0;
    data.con = mlx_init();
    data.wind = mlx_new_window(data.con, SIZE_X, SIZE_Y, "EPIC");
    data.img = mlx_new_image(data.con, SIZE_X, SIZE_Y);
    data.img_d = mlx_get_data_addr(data.img, (&data.bpp), (&data.line), (&data.end));
    if (data.wind == NULL || data.img_d == NULL)
        ft_putstr("NULL ALERT");
    printf("bpp: %i,  size_line: %i,  endian: %i\n", data.bpp, data.line, data.end);
    mlx_key_hook(data.wind, ft_key_pressed, &data);
    mlx_loop(data.con);
}