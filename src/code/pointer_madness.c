#include <stdio.h>
#include <dos.h>

int main(int argc, char** argv){

  far void* a = FP_SEG(0x0000) + FP_OFF(0x0120);
  far void* b = FP_SEG(0x0010) + FP_OFF(0x0020);
  far void* c = FP_SEG(0x0012) + FP_OFF(0x0000);

  printf("%b",a==b);
  printf("%b",a==c);
  printf("%b",b==c);
}