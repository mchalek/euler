#include <stdio.h>
#include <stdlib.h>

int ipow(int a, unsigned int b)
{
    int i;
    int ret = 1;
    for(i = 0; i < b; i++)
        ret *= a;
    return ret;
}

int main(int argc, char **argv)
{
    if(argc != 2)
        return -1;

    int n = atoi(argv[1]);

    unsigned long long *F;
    int nF = ipow(3, 10) - 1;
    int i;
    for(i = 0; i < nF; i++)
    

}
