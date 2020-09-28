#include <stdio.h>
#include <stdlib.h>
#include "modules.c"

int main()
{
    // unsigned long long t = initPerm(211523234124);
    // printf("%llu\n",t);

    // unsigned long long T = finalPerm(t);
    // printf("%llu\n",T);

    

    // unsigned long long test = ULLONG_MAX;
    // printf("%llu\n",test);

    
    // test = PC1_perm(test);
    // printf("%llu\n",test);

    
    // test = PC2_perm(test);
    // printf("%llu\n",test);


    uint64 key = 0x0000000000000000;
    uint64 plaintext = 0x0000000000000000;
    printf("%llu\n",encryption(key, plaintext));

    uint64 t = 0x8CA64DE9C1B123A7;
    printf("%llu\n",t);
    
    // uint64 *subkeySet= (uint64 *) malloc(17 * sizeof(uint64));

    // genSubKeys(key, subkeySet);

    // for(int i = 1; i <= 16; i++)
    // {
    //     printf("k_%2d : %llu\n", i, subkeySet[i]);
    //     //print64(subkeySet[i]);
    // }

}