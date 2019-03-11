#include <stdio.h>
#include <dos.h>

int main(int argc, char** argv){

  void far *a = MK_FP(0x0000, 0x0120);
  void far *b = MK_FP(0x0010, 0x0020);
  void far *c = MK_FP(0x0012, 0x0000);

  printf("%d\n",a==b);
  printf("%d\n",a==c);
  printf("%d\n",b==c);
}