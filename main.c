#include <stdio.h>
#include <stdlib.h>
#include "modules.c"

int main()
{

    uint64 key = 0x133457799BBCDFF1;
    uint64 msg = 0x0123456789ABCDEF;

    //// 1. test generate key

    // uint64 *subkeys = (uint64) malloc (17 * sizeof(uint64));
    // genSubKeys(key, subkeys);

    // for(int i = 1; i <= 16; i++)
    // {
    //     printf("k_i : ");
    //     print64n(subkeys[i], 48);
    // }

    //// checked!

    //// 2. test IP / E - expansion
    // uint64 ip = initPerm(msg);
    // print64(ip);
    //// checked!

    //// 3. test encrpt
    //// checked!

    //// 4. test decrypt
    //// checked!




    uint64 cipher = encryption(key, msg);
    uint64 t = decryption(key,cipher);

    print64(msg);
    print64(t);
   
}