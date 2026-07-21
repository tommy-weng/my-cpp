// Example program
#include <stdio.h>
#include <stddef.h>

#define my_container_of(ptr, type, member) ({                      \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type, member) );})


typedef struct
{
    int a;
    int b;
    double c;
    int d;
} CC;


int main()
{
  CC cc = {1,2,3.3,4};
  
  double *pc = &cc.c;
  
  printf("value = %d\n",my_container_of(pc, CC, c)->d);
}

