#include "dataStructures.h"

unsigned long long perm(unsigned long long input, short table[], int n)
{
    unsigned long long ret = 0;
    for(int i = 0; i < n; i++)
    {
        unsigned long long t = (input >> (table[i] - 1) & 1);
        t = t << i;
        ret = ret | t;
    }
    return ret;
}

/* Initial Permutation
 * input : 64 bits plain text
 * output: 64 bits concatenation of L0 and R0
 */ 
unsigned long long initPerm(unsigned long long M)
{
    // unsigned long long ret = 0;
    // for(int i = 0; i < 64; i++)
    // {
    //     unsigned long long t = (M >> (IP[i] - 1) & 1);
    //     t = t << i;
    //     ret = ret | t;
    // }
    // return ret;
    return perm(M, IP, 64);
}


/* Final Permutation
 * input : 64 bits concatenation of L0 and R0
 * output: 64 bits cipher text
 */ 
unsigned long long finalPerm(unsigned long long M)
{
    // unsigned long long ret = 0;
    // for(int i = 0; i < 64; i++)
    // {
    //     unsigned long long t = (M >> (FP[i] - 1) & 1);
    //     t = t << i;
    //     ret = ret | t;
    // }
    // return ret;
    return perm(M, FP, 64);
}


/* E-Expansion
 * input : 32 bits R_i-1
 * output: 48 bits E(R_i-1)
 */ 

unsigned long long E_expansion(unsigned long long R)
{
    return perm(R, E, 48);
}

unsigned long long PC1_perm(unsigned long long K64)
{
    return perm(K64, PC1, 56);
}

unsigned long long PC2_perm(unsigned long long K56)
{
    return perm(K56, PC2, 48);
}

