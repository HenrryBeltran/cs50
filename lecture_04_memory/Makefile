CC = clang
CFLAGS = -Wall -Werror -std=c11
LDLIBS = -lcs50 -lm

%: %.c
	@$(CC) $(CFLAGS) -o $@ $< $(LDLIBS) > /dev/null


