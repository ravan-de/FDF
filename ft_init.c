#include <stdlib.h>
#include "libft.h"
#include "mlx.h"
#include "fdf.h"
#include "printf.h"
#include <math.h>

void     transform(int x, int y, int z, t_mlx *data)
{
    double *vect;
    double *vect2;
    double *vect3;

    vect = vect_x_matrix(data->x_start + x, data->y_start + y, z, data->rotx);
    vect2 = vect_x_matrix(vect[0], vect[1], vect[2], data->roty);
    vect3 = vect_x_matrix(vect2[0], vect2[1], vect2[2], data->rotz);
    data->x_end = round(vect2[0]);
    data->y_end = round(vect2[1]);
    free(vect);
    free(vect2);
    free(vect3);
}

void     transform_draw(int x, t_splitlst *lst, t_mlx *data)
{
    static int  x_prevline = SIZE_X / 3;//stores ending of previos line's first point to know where to draw;
    static int  y_prevline = SIZE_Y / 3;
    static int  x_prev = SIZE_X / 3;
    static int  y_prev = SIZE_Y / 3;

    data->x_start = x_prev;
    data->y_start = y_prev;
    if (x + 1 < lst->size)
    {
        if (x == 0)
        {
            data->x_start = x_prevline;
            data->y_start = y_prevline;
        }
        data->color = 1000;
        transform(SCALE, 0, SCALE * lst->split[x + 1], data);
        ft_printf("-> from:(%i,%i)  to:(%i,%i)\n", data->x_start, data->y_start, data->x_end, data->y_end);
        ft_draw(data);
        x_prev = data->x_end;
        y_prev = data->y_end;
    }
    if (lst->next != NULL && x < lst->next->size)
    {
        data->color = 20000;
        transform(0, SCALE, SCALE * lst->next->split[x], data);
        ft_printf("|  from:(%i,%i)  to:(%i,%i)\n", data->x_start, data->y_start, data->x_end, data->y_end);
        ft_draw(data);
        if (x == 0)
        {
            x_prevline = data->x_end;
            y_prevline = data->y_end;
        }
    }
}

//only do this if perspective changes or on first launch
void     ft_loop_grid(t_mlx *data)
{
    int         x;
    int         y;
    t_splitlst  *lst = data->grid;

    y = 0;
    while (lst != NULL)
    {
        x = 0;
        while (x < lst->size)
        {
            ft_printf("x:%i  y:%i\n", x, y);
            transform_draw(x, lst, data);
            x++;
        }
        lst = lst->next;
        y++;
    }
}

int     ft_key_pressed(int keycode, t_mlx *data)
{
    data->x_start = SIZE_X / 3;
    data->y_start = SIZE_Y / 3;
    if (keycode == 53) //escape
        exit(0);
    if (keycode == 36) //enter
        ft_loop_grid(data); //isometric
    if (keycode == 17)
    {
        data->x_end = data->x_start;
        data->y_end = 100;
        ft_printf("x_start:%i -> x_end:%i\n", data->x_start, data->x_end);
        ft_printf("y_start:%i -> y_end:%i\n", data->y_start, data->y_end);
        ft_draw(data);
    }
    return (0);
}

void    ft_init_rotx(t_mlx *data, double a)
{
    data->rotx = malloc(sizeof(double *) * 3);
    data->rotx[0] = malloc(sizeof(double) * 3);
    data->rotx[1] = malloc(sizeof(double) * 3);
    data->rotx[2] = malloc(sizeof(double) * 3);
    data->rotx[0][0] = 1;
    data->rotx[0][1] = 0; 
    data->rotx[0][2] = 0;
    data->rotx[1][0] = 0;
    data->rotx[1][1] = cos(a);
    data->rotx[1][2] = sin(a);
    data->rotx[2][0] = 0;
    data->rotx[2][1] = -1 * sin(a);
    data->rotx[2][2] = cos(a);
}

void    ft_init_roty(t_mlx *data, double b)
{
    data->roty = malloc(sizeof(double *) * 3);
    data->roty[0] = malloc(sizeof(double) * 3);
    data->roty[1] = malloc(sizeof(double) * 3);
    data->roty[2] = malloc(sizeof(double) * 3);
    data->roty[0][0] = cos(b);
    data->roty[0][1] = 0; 
    data->roty[0][2] = -1 * sin(b);
    data->roty[1][0] = 0;
    data->roty[1][1] = 1;
    data->roty[1][2] = 0;
    data->roty[2][0] = sin(b);
    data->roty[2][1] = 0;
    data->roty[2][2] = cos(b);
}

void    ft_init_rotz(t_mlx *data, double g)
{
    data->rotz = malloc(sizeof(double *) * 3);
    data->rotz[0] = malloc(sizeof(double) * 3);
    data->rotz[1] = malloc(sizeof(double) * 3);
    data->rotz[2] = malloc(sizeof(double) * 3);
    data->rotz[0][0] = cos(g);
    data->rotz[0][1] = -1 * sin(g);
    data->rotz[0][2] = 0;
    data->rotz[1][0] = sin(g);
    data->rotz[1][1] = cos(g);
    data->rotz[1][2] = 0;
    data->rotz[2][0] = 0;
    data->rotz[2][1] = 0;
    data->rotz[2][2] = 1;
}

void    ft_init(t_splitlst *lst)
{
    (void)lst;
    t_mlx   data;
    double  a;
    double  b;
    double  g;

    a = 0;//asin(tan((30 * M_PI / 180)));
    b = 0;//45 * M_PI / 180;
    g = 10 * RAD;
    data.con = mlx_init();
    data.wind = mlx_new_window(data.con, SIZE_X, SIZE_Y, "EPIC");
    data.grid = lst;
    ft_init_rotx(&data, a);
    ft_init_roty(&data, b);
    ft_init_rotz(&data, g);
    if (data.wind == NULL)
        return ;
    mlx_key_hook(data.wind, ft_key_pressed, &data);
    mlx_loop(data.con);
}

/* plan voor render(geld voor elk punt vanaf punt (0,0): 
    1. maak lijn rechts(split[x + 1]) in 3d, projecteer deze naar window. 
    2. maak lijn onder(lst->next.split[x]) in 3d, projecteer deze naar window.

    manipuleerbare camera in 3d(xcam, ycam, zcam, look).
*/