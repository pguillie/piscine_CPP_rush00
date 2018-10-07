# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oyagci <oyagci@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 10:27:13 by oyagci            #+#    #+#              #
#    Updated: 2018/10/01 16:52:47 by oyagci           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#   Variables

NAME    = ft_retro
CC      = clang++
FLAGS   = -Wall -Wextra -Werror
LIBS	= -lncurses
HEADER  = includes/
SRCDIR  = ./
OBJDIR  = ./
SRC     = main.cpp \
	    Character.cpp \
	    Entity.cpp \
	    Game.cpp \
	    Missile.cpp \
	    Player.cpp \
	    Weapon.cpp \
	    Window.cpp \
	    Enemy.cpp
SRCS    = $(addprefix $(SRCDIR), $(SRC))
OBJS    = $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(FLAGS) $(LIBS)

$(OBJDIR):
	mkdir -p objs

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(FLAGS) -c -o $@ $< -I $(HEADER)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
