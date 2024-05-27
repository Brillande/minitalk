SERVER = server
CLIENT = client

CFLAGS = -Wall -Werror -Wextra
CC = gcc
FLAGS = -Wall -Wextra -Werror -L ./printf -lftprintf

PRINTF = ./printf

all: $(SERVER) $(CLIENT)

$(SERVER): server.c $(PRINTF)/libftprintf.a
	$(CC) $(CFLAGS) $< -o $@ -L $(PRINTF) -lftprintf

$(CLIENT): client.c $(PRINTF)/libftprintf.a
	$(CC) $(CFLAGS) $< -o $@ -L $(PRINTF) -lftprintf

$(PRINTF)/libftprintf.a:
	@make -C $(PRINTF)

clean:
	@make clean -s -C $(PRINTF)
	@rm -f $(SERVER) $(CLIENT)

fclean: clean
	@make fclean -s -C $(PRINTF)

re: fclean all