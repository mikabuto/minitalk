S_NAME = server
C_NAME = client

S_SRC = server.c
C_SRC = client.c

S_SRC_BONUS = server_bonus.c
C_SRC_BONUS = client_bonus.c

S_OBJ = $(S_SRC:.c=.o)
C_OBJ = $(C_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(S_NAME) $(C_NAME)

bonus: 
	make S_SRC="$(SRC_BONUS_C)" S_SRC="$(S_SRC_BONUS)" all

$(S_NAME): $(S_OBJ) libft
	$(CC) -o $@ $< -Llibft -lft

$(C_NAME): $(C_OBJ) libft
	$(CC) -o $@ $< -Llibft -lft

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft

clean:
	rm -f $(S_OBJ) $(C_OBJ)
	make -C libft clean
	
fclean: clean
	rm -f $(S_NAME) $(C_NAME) libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re