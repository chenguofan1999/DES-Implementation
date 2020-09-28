#include <stdio.h>
#include <stdlib.h>
#include "modules.c"

int main()
{

    uint64 key = 0x133457799BBCDFF1;
    uint64 msg = 0x0123456789ABCDEF;

    // 1. test generate key
    uint64 *subkeys = (uint64) malloc (17 * sizeof(uint64));
    genSubKeys(key, subkeys);

   
}