# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/01 19:56:59 by grevenko          #+#    #+#              #
#    Updated: 2018/02/07 18:26:07 by grevenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	RTv1

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

INCFLAGS	=	$(addprefix -I, includes libft)

SRCDIR		=	source

INCDIR		=	includes

SRC			=	event.c main.c vector.c

HEADERS		=	$(addprefix $(INCDIR)/, header.h)

LIBS		=	libft/libft.a

OBJDIR		=	obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) -O3 -o $(NAME) $(OBJ) ${LIBS} -lmlx -framework OpenGL -framework AppKit $(INCFLAGS)

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
