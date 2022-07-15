OBJ = obj/main.o\
	obj/helpers.o\
	obj/string_mgmt.o\
	# obj/blockchain.o\

CFLAGS += -Iinclude # -g3 -fsanitize=address # -Wall -Wextra -Werror

HEADER = include/main.h\
	include/blockchain.h\
	include/helpers.h\
	include/string_mgmt.h\
	include/dbg.h\

BIN = bin/my_blockchain
CC = gcc
RM = -rf

all: my_blockchain

my_blockchain: $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(CFLAGS)

obj/main.o: src/main.c
	${CC} ${CFLAGS} -c $< -o $@
# obj/blockchain.o: src/blockchain.c
#	${CC} ${CFLAGS} -c $< -o $@
obj/helpers.o: src/helpers.c
	${CC} ${CFLAGS} -c $< -o $@
obj/string_mgmt.o: src/string_mgmt.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) bin/my_blockchain bin/*.dSYM obj/*