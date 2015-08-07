#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


static inline long long unsigned time_ns(struct timespec* const ts) {
  if (clock_gettime(CLOCK_REALTIME, ts)) {
    exit(1);
  }
  return ((long long unsigned) ts->tv_sec) * 1000000000LLU
    + (long long unsigned) ts->tv_nsec;
}

int main(void) {
  const int iterations = 10000000;
  struct timespec ts;
  long long unsigned start_ns;
  char c;	
  int fd;

  fd = open( "/dev/zero", O_RDWR);	
  start_ns = time_ns(&ts);	
  for (int i = 0; i < iterations; i++) {
    if (syscall(SYS_read, fd, &c, 1) <0) {
      exit(2);
    }
  }
  const long long unsigned delta = time_ns(&ts) - start_ns;
  printf("%i read system calls in %lluns (%.1fns/syscall)\n",
         iterations, delta, (delta / (float) iterations));
  return 0;
}
