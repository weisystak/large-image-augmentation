#include "stdio.h"
#include <stdlib.h>

struct A{
    struct A* n;
    int val;
};
int main()
{
    
    struct A a;
    struct A b;
    a.n = &b;

}