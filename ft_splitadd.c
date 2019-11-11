#include "fdf.h"
#include <stdlib.h>


t_splitlst  *ft_splitadd(t_splitlst *node, t_splitlst *end)
{
    while (end->next != NULL)
        end = end->next;
    end->next = node;
    return (node);
}