CC = gcc
CFLAGS = -Wall -Wextra

SRCS := $(wildcard source/*.c)

OBJS := $(SRCS:.c=.o)

all: csq

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

csq: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) csq
