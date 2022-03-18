# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikabuto <mikabuto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 14:16:43 by mikabuto          #+#    #+#              #
#    Updated: 2022/03/14 14:16:43 by mikabuto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S_NAME = server
C_NAME = client

S_SRC = server_mandatory.c
C_SRC = client_mandatory.c

S_SRC_BONUS = server_bonus.c
C_SRC_BONUS = client_bonus.c

S_OBJ = $(S_SRC:.c=.o)
C_OBJ = $(C_SRC:.c=.o)

S_OBJ_BONUS = $(S_SRC_BONUS:.c=.o)
C_OBJ_BONUS = $(C_SRC_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a

all: $(LIBFT) $(S_NAME) $(C_NAME)

bonus: 
	@make S_SRC="$(S_SRC_BONUS)" C_SRC="$(C_SRC_BONUS)" all

$(S_NAME): $(S_OBJ)
	$(CC) -o $@ $< -Llibft -lft

$(C_NAME): $(C_OBJ)
	$(CC) -o $@ $< -Llibft -lft

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	rm -f $(S_OBJ) $(C_OBJ) $(S_OBJ_BONUS) $(C_OBJ_BONUS)
	@make -C libft clean
	
fclean: clean
	rm -f $(S_NAME) $(C_NAME) libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re