# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/01 19:56:59 by grevenko          #+#    #+#              #
#    Updated: 2018/03/19 18:40:34 by grevenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	RTv1

CC			=	gcc

CFLAGS		=	

INCFLAGS	=	$(addprefix -I, includes libft minilibx_macos)

SRCDIR		=	source

INCDIR		=	includes

SRC			=	color.c cone.c cylinder.c error.c error2.c event.c light.c main.c plane.c ray_tracing.c read_fig.c read_light.c read_utils.c read.c sphere.c utils.c vector.c vector2.c

HEADERS		=	$(addprefix $(INCDIR)/, header.h)

LIBS		=	libft/libft.a minilibx_macos/libmlx.a

OBJDIR		=	obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C minilibx_macos
	$(CC) -O3 -o $(NAME) $(OBJ) ${LIBS} -framework OpenGL -framework AppKit $(INCFLAGS)

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	make -C libft clean;
	rm -rf $(OBJDIR);

fclean: clean
	make -C libft fclean;
	rm -f $(NAME);

re: fclean all
