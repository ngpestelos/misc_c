#include <stdio.h>

struct foo
{
  int a;
  int b;
};

void test(struct foo f)
{
  f.a = 10;
  
  printf("inside test: %d %p\n", f.a, &f);
}

int main(void)
{
  struct foo f;
  f.a = 0;
  f.b = 1;
  
  test(f);

  // struct should have different addresses
  printf("outside %d %p\n", f.a, &f);

  return 0;
}
