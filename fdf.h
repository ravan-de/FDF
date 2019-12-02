#ifndef _FDF_H
# define _FDF_H

#include <math.h>

typedef struct          s_splitlst
{
    int                 *split;
    short               size;
    struct s_splitlst   *next;
}                       t_splitlst;

typedef struct  s_mlx
{
    t_splitlst  *grid;
    void        *con;
    void        *wind;
    double      **rotx;
    double      **roty;
    double      **rotz;
    int         x_end;
    int         y_end;
    int         x_start;
    int         y_start;
    int         color;
}               t_mlx;


# define SIZE_X 2000
# define SIZE_Y 1000
# define SCALE 20
# define RAD M_PI / 180

t_splitlst  *ft_splitnew(int *split, short size);
t_splitlst  *ft_splitadd(t_splitlst *node, t_splitlst *end);
void        ft_init(t_splitlst *lst);
void        nb_x_matrix(double nb, double **matrix);
double      *vect_x_matrix(double x, double y, double z, double **matrix);
void        print_matrix(double **matrix);
void        ft_line_steep(int dx, int dy, t_mlx *data);
void        ft_line(int dx, int dy, t_mlx *data);
void        ft_line_vert(int dy, t_mlx *data);
void        ft_draw(t_mlx *data);
int         abs(int nb);

#endif