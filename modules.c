#include "tables.h"

typedef unsigned long long uint64;
uint64 perm(uint64 input, short table[], int n)
{
    uint64 ret = 0;
    for(int i = 0; i < n; i++)
    {
        uint64 t = (input >> (table[i] - 1) & 1);
        t = t << i;
        ret = ret | t;
    }
    return ret;
}

void print64(uint64 num)
{
    printf("%llu\n",num);
    for(int i = 63; i >= 0; i--)
        printf("%llu", num>>i & 1);
    printf("\n");
}

/* Initial Permutation
 * input : 64 bits plain text
 * output: 64 bits concatenation of L0 and R0
 */ 
uint64 initPerm(uint64 M)
{
    return perm(M, IP, 64);
}


/* Final Permutation
 * input : 64 bits concatenation of L0 and R0
 * output: 64 bits cipher text
 */ 
uint64 finalPerm(uint64 M)
{
    return perm(M, FP, 64);
}


/* E-Expansion
 * input : 32 bits R_i-1
 * output: 48 bits E(R_i-1)
 */ 
uint64 E_expansion(uint64 R)
{
    return perm(R, E, 48);
}

uint64 PC1_perm(uint64 K64)
{
    return perm(K64, PC1, 56);
}

uint64 PC2_perm(uint64 K56)
{
    return perm(K56, PC2, 48);
}


void genSubKeys(uint64 K, uint64 *subkeys)
{   
    uint64 C0D0 = PC1_perm(K);

    // printf("After PC1 perm : %llu\n", C0D0);
    // for(int i = 63; i >= 0; i--)
    //     printf("%llu", C0D0>>i & 1);
    // printf("\n");

    uint64 C[17], D[17];

    D[0] = (C0D0 << 36) >> 36;

    // for(int i = 63; i >= 0; i--)
    //     printf("%llu", D[0]>>i & 1);
    // printf("\n");

    C[0] = C0D0 >> 28 ;

    // for(int i = 63; i >= 0; i--)
    //     printf("%llu", C[0]>>i & 1);
    // printf("\n");

    for(int i = 1; i <= 16; i++)
    {
        if(i == 1 || i == 2 || i == 9 || i == 16)
        {
            // left cyclic shift 1 bit

            // record the highest bit
            uint64 tc = C[i-1] >> 27;
            // left shift 1 bit
            C[i] = C[i-1] << 1;
            // cp highest bit to lowest bit
            C[i] = C[i] | tc;
            // cut the 29th bit
            C[i] = (C[i] << 36) >> 36;

            // the same 
            uint64 td = D[i-1] >> 27;
            D[i] = D[i-1] << 1;
            D[i] = D[i] | td;
            D[i] = (D[i] << 36) >> 36;
        }
        else
        {
            // left cyclic shift 2 bits

            // record the highest 2 bits
            uint64 tc = C[i-1] >> 26;
            // left shift 2 bits
            C[i] = C[i-1] << 2;
            // cp highest 2 bits to lowest 2 bits
            C[i] = C[i] | tc;
            // cut the 29th and 30th bits
            C[i] = (C[i] << 36) >> 36;

            //the same
            uint64 td = D[i-1] >> 26;
            D[i] = D[i-1] << 2;
            D[i] = D[i] | td;
            D[i] = (D[i] << 36) >> 36;
        }
        int concat = (C[i] << 28) | D[i];
        subkeys[i] = PC2_perm(concat);

        // printf("i = %d\n", i);
        // printf("C[%d] = %llu\n", i, C[i]);
        // printf("D[%d] = %llu\n", i, D[i]);
        // printf("before PC2 : %llu\n", concat);
        // printf("before PC2 : %llu\n", subkeys[i]);
    }
}