
/**
 * The test bench to test the CPU.
 * Copyright (C) 2018 Johann Lee <me@qinka.pro>
 * (GPLv3 License)
 */

#define __USE_GNU
#define __UCLIBC_LINUX_SPECIFIC__

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sched.h>


/**
 * test kernel
 *
 * a=2*a+b−c−d+5
 * b=2*b+c−d−a+1
 * c=2*c+d−b−a−3
 * d=2*d+a−b−c+1 
 *
 */

void test_kernel(uint32_t* a, uint32_t *b, uint32_t *c, uint32_t *d) {
  volatile uint64_t A, B, C, D;
  A = *a + *a + *b - *c - *d + 5;
  B = *b + *b + *c - *d - *a + 1;
  C = *c + *c + *d - *a - *b - 3;
  D = *d + *d + *a - *b - *c + 1;
  *a = A;
  *b = B;
  *c = C;
  *d = D;
  return;
}

void test_function() {
  uint32_t a = 1, b = 2, c = 3, d = 4;
  while (d < 0x1FFFFFFF)
    test_kernel(&a, &b, &c, &d);
  printf("a=%u\nb=%u\nc=%u\nd=%u\n",a,b,c,d);

  return;
}

int main (int argc,char** argv) {
  struct timeval start, end;

  int set;
  cpu_set_t core_mask;

  if (argc < 2) {
    set = 0;
  }
  else {
    set = argv[1][0] - '0';
  }


  CPU_ZERO(&core_mask);
  CPU_SET(set, &core_mask);
  sched_setaffinity(0,sizeof(cpu_set_t),&core_mask);

  gettimeofday(&start,NULL);
  test_function();
  gettimeofday(&end,NULL);

  long diff = end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec;

  printf("Score: %ld\n", diff);
  return 0;
}



