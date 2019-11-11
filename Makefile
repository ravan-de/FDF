#******************************************************************************#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ravan-de <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/03/21 15:13:41 by ravan-de      #+#    #+#                  #
#    Updated: 2019/04/29 18:44:14 by ravan-de      ########   odam.nl          #
#                                                                              #
#******************************************************************************#

NAME = test

LIB = libft/libft.a libft/libmlx.a

INCL = libft/includes

OBJ = ft_splitnew.o ft_splitadd.o read_data.o ft_init.o

all: $(NAME)

$(LIB):
	cd libft && $(MAKE)

%.o: %.c
	gcc -c -I $(INCL) -Wall -Wextra -Werror -o $@ $^

$(NAME): $(LIB) $(OBJ)
	gcc -o $(NAME) -I $(INCL) -Wall -Wextra -Werror -framework OpenGL -framework AppKit $(OBJ) $(LIB)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all