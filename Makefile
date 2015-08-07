CC = gcc
CFLAGS = -march=native -O3 -D_XOPEN_SOURCE=600 -D_GNU_SOURCE -std=c99 \
         -W -Wall -Werror
LDFLAGS = -lrt -lpthread

TARGETS = timectxsw timectxswws timesyscall timetctxsw timetctxsw2 timereadcall \
	  timewritecall


all: bench

bench: $(TARGETS)
	./cpubench.sh

clean:
	rm -f $(TARGETS)

.PHONY: all bench
