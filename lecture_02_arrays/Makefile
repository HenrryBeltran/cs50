CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
LDLIBS = -lcs50 -lm

%: %.c
	@$(CC) $(CFLAGS) -o $@ $< $(LDLIBS) > /dev/null
