# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirokiurabe <hirokiurabe@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 22:09:59 by hirokiurabe       #+#    #+#              #
#    Updated: 2025/02/10 23:01:52 by hirokiurabe      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = bsq
CXX      = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23
SRCS     = bsq.cpp
OBJS     = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp bsq.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re