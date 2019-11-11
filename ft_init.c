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

//only do this if perspective changes or on first launch
int    ft_loop_grid(void *param)
{
    int         x;
    t_mlx       *data = (t_mlx *)param;
    t_splitlst  *lst = data->grid;

    x = 0;
    while (lst != NULL)
    {
        x = 0;
        while (x < lst->size)
        {
            //ft_putnbr(lst->split[x]);
            //ft_putchar(' ');
            if (x + 1 < lst->size)
                ft_putstr("dikke");//draw_line_right(lst->split[x], lst->split[x + 1]);
            if (lst->next != NULL && x < lst->next->size)
                ft_putstr("test");//draw_line_down(lst->split[x], lst->next->split[x]);
            x++;
        }
        //ft_putendl("");
        lst = lst->next;
    }
    return (0);
}

void    ft_init(t_splitlst *lst)
{
    (void)lst;
    t_mlx   data;

    data.con = mlx_init();
    data.wind = mlx_new_window(data.con, SIZE_X, SIZE_Y, "EPIC");
    data.grid = lst;
    if (data.wind == NULL)
        return ;
    mlx_key_hook(data.wind, ft_key_pressed, &data);
    mlx_loop_hook(data.con, ft_loop_grid, &data);
    mlx_loop(data.con);
}

/* plan voor render(geld voor elk punt vanaf punt (0,0): 
    1. maak lijn rechts(split[x + 1]) in 3d, projecteer deze naar window. 
    2. maak lijn onder(lst->next.split[x]) in 3d, projecteer deze naar window.
*/