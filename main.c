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

    // uint64 *subkeySet= (uint64 *) malloc(17 * sizeof(uint64));

    // genSubKeys(key, subkeySet);

    // for(int i = 1; i <= 16; i++)
    // {
    //     printf("k_%2d : %llu\n", i, subkeySet[i]);
    //     //print64(subkeySet[i]);
    // }

// main:
    // uint64 key = 0x00700C00D000A000;
    // uint64 plaintext = 0x0F00D06005000000;
    // uint64 cipherText = encryption(key, plaintext);
    // uint64 maybePlain = decryption(key, cipherText);
    // print64(cipherText);
    // print64(maybePlain);

// test of Festel:
    // uint64 subkey1 = 0x0000ABCDEF123456;
    // uint64 subkey2 = 0x0000BDCAFE666666;
    // uint64 subkey3 = 0x00002DC02E689666;

    // uint64 text = 0x000000009ABCDEF0;

    // Feistel(text, subkey1);
    // printf("\n\n");
    // Feistel(text, subkey2);
    // printf("\n\n");
    // Feistel(text, subkey3);

// test of genSubkeys:
    uint64 key = 0x00000FF00FF00FF0;
    uint64 *subkeys = (uint64*) malloc (17 * sizeof(uint64));
    genSubKeys(key, subkeys);

    for(int i = 1; i <= 16; i++)
    {
        printf("k_%d: \n", i);
        print64(subkeys[i]);
    }
}