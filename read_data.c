#include <fcntl.h>
#include <unistd.h>
#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"

int             *strarr_intarr(char **strsplit)
{
    int i;
    int *split;

    i = 0;
    while (strsplit[i] != NULL)
        i++;
    split = ft_memalloc(sizeof(int) * i); 
    split[i] = __INT_MAX__;
    while (i > 0)
    {
        split[i - 1] = ft_atoi(strsplit[i - 1]);
        free(strsplit[i - 1]);
        i--;
    }
    free(strsplit);
    return (split);
}

t_splitlst      *read_data(int fd)
{
    int         y;
    char        *str;
    char        **split;
    t_splitlst  *start;
    t_splitlst  *end;

    y = 0;
    start = NULL;
    end = NULL;
    str = ft_strnew(0);
    while (get_next_line(fd, &str) == 1)
    {
        split = ft_strsplit(str, ' ');
        if (y == 0)
        {
            start = ft_splitnew(strarr_intarr(split));
            end = start;
        }
        else
            end = ft_splitadd(ft_splitnew(strarr_intarr(split)), end);
        y++;
    }
    return (start);
}

void    ft_printlst(t_splitlst *start)
{
    int     x;

    while (start != NULL)
    {
        x = 0;
        while (start->split[x] != __INT_MAX__)
        {
            ft_putnbr(start->split[x]);
            if (start->split[x] >= 10)
                ft_putstr(" ");
            else
                ft_putstr("  ");
            x++;            
        }
        ft_putendl("");
        start = start->next;
    }
}

int main(int argc, char **argv)
{
    t_splitlst *lst;

    lst = NULL;
    if (argc == 2)
    {
        lst = read_data(open(argv[1], O_RDONLY));
        ft_printlst(lst);
        ft_init(lst);
    }
    return (0);
}