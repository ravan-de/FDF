#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

t_splitlst  *ft_splitnew(int *split, short size)
{
    t_splitlst  *node;
    node = (t_splitlst *)ft_memalloc(sizeof(t_splitlst));
    if (node == NULL)
        return (NULL);
    node->split = split;
    node->size = size;
    node->next = NULL;
    return (node);
}