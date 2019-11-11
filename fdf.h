#ifndef _FDF_H
# define _FDF_H

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
}               t_mlx;


# define SIZE_X 1000
# define SIZE_Y 500

t_splitlst  *ft_splitnew(int *split, short size);
t_splitlst  *ft_splitadd(t_splitlst *node, t_splitlst *end);
void        ft_init(t_splitlst *lst);

#endif