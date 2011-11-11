#include <stdio.h>

int main(void) {
  int a = 13;
  int b = 26;

  // How to swap two ints without a temp variable
  a = a ^ b;
  b = b ^ a;
  a = a ^ b;
  
  printf("%d %d", a, b);

  return 0;
}