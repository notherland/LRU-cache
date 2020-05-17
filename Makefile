CFLAGS = -g -O2 -MD

all: spisok.out

test: test.out

test.out: main1.o hash_table.o cache.o input.o run_tests.o
	  $(CC) $(CFLAGS) -o $@ $^

spisok.out: main.o hash_table.o cache.o input.o
		$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $<

-include *.d

.PHONY: clean

clean:
		rm *.o *.d *.out
