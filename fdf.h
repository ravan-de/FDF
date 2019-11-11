#ifndef _FDF_H
# define _FDF_H

typedef struct          s_splitlst
{
    int                 *split;
    struct s_splitlst   *next;
}                       t_splitlst;

typedef struct  s_mlx
{
    void        *con;
    void        *wind;
    void        *img;
    char        *img_d;
    int         bpp;
    int         line;
    int         end;         
}               t_mlx;


# define SIZE_X 1000
# define SIZE_Y 500

t_splitlst  *ft_splitnew(int *split);
t_splitlst  *ft_splitadd(t_splitlst *node, t_splitlst *end);
void        ft_init(t_splitlst *lst);

#endif