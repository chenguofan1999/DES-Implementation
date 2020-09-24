#include <stdio.h>
#include <stdlib.h>
#include "modules.c"

int main()
{
    // unsigned long long t = initPerm(211523234124);
    // printf("%llu\n",t);

    // unsigned long long T = finalPerm(t);
    // printf("%llu\n",T);

    unsigned long long key = 0x7ABC7A62F3498EBC;

    unsigned long long *subkeySet= (unsigned long long*) malloc(17 * sizeof(unsigned long long));

    genSubKeys(key, subkeySet);

    for(int i = 1; i <= 16; i++)
    {
        printf("k_%2d : %llu\n", i, subkeySet[i]);
    }

}