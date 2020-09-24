#include "tables.h"

//typedef unsigned long long block;
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


void genSubKeys(unsigned long long K, unsigned long long *subkeys)
{   
    unsigned long long C0D0 = PC1_perm(K);
    unsigned long long C[17], D[17];
    D[0] = (C0D0 << 36) >>36;
    C[0] = C0D0 >> 28;

    for(int i = 0; i <= 16; i++)
    {
        if(i == 1 || i == 2 || i == 9 || i == 16)
        {
            // left cyclic shift 1 bit

            // record the highest bit
            unsigned long long tc = C[i-1] >> 27;
            // left shift 1 bit
            C[i] = C[i-1] << 1;
            // cp highest bit to lowest bit
            C[i] = C[i] | tc;
            // cut the 29th bit
            C[i] = (C[i] << 36) >> 36;

            // the same 
            unsigned long long td = D[i-1] >> 27;
            D[i] = D[i-1] << 1;
            D[i] = D[i] | td;
            D[i] = (D[i] << 36) >> 36;
        }
        else
        {
            // left cyclic shift 2 bits

            // record the highest 2 bits
            unsigned long long tc = C[i-1] >> 26;
            // left shift 2 bits
            C[i] = C[i-1] << 2;
            // cp highest 2 bits to lowest 2 bits
            C[i] = C[i] | tc;
            // cut the 29th and 30th bits
            C[i] = (C[i] << 36) >> 36;

            //the same
            unsigned long long td = D[i-1] >> 26;
            D[i] = D[i-1] << 2;
            D[i] = D[i] | td;
            D[i] = (D[i] << 36) >> 36;
        }
        int concat = (C[i] << 28) | D[i];
        subkeys[i] = PC2_perm(concat);
    }
}