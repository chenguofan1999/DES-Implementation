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
 * input : 64-bit plain text
 * output: 64-bit concatenation of L0 and R0
 */ 
uint64 initPerm(uint64 M)
{
    return perm(M, IP, 64);
}


/* Final Permutation
 * input : 64-bit concatenation of L0 and R0
 * output: 64-bit cipher text
 */ 
uint64 finalPerm(uint64 M)
{
    return perm(M, FP, 64);
}


/* E-Expansion
 * input : 32-bit R_i-1
 * output: 48-bit E(R_i-1)
 */ 
uint64 E_expansion(uint64 R)
{
    return perm(R, E, 48);
}

/* PC1_perm in subkey generation
 * input : 64-bit key
 * output: 56-bit 
 */ 
uint64 PC1_perm(uint64 K64)
{
    return perm(K64, PC1, 56);
}

/* PC1_perm in subkey generation
 * input : 56-bit
 * output: 48-bit 
 */ 
uint64 PC2_perm(uint64 K56)
{
    return perm(K56, PC2, 48);
}

/* P_perm in Feistel func
 * input : 32-bit
 * output: 32-bit 
 */ 
uint64 P_perm(uint64 x)
{
    return perm(x, P, 32);
}


void genSubKeys(uint64 K, uint64 *subkeys)
{   
    uint64 C0D0 = PC1_perm(K);
    uint64 C[17], D[17];

    D[0] = (C0D0 << 36) >> 36;
    C[0] = C0D0 >> 28 ;

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
    }
}

/* Feistel
 * input : a 32-bit text and a 48-bit subkey
 * output: a 32-bit text
 */ 
uint64 Feistel(uint64 text, uint64 subkey)
{
    // 1. E-扩展至48位
    text = E_expansion(text);

    // 2. 按位异或
    text = text ^ subkey;

    // 3. S-box transform -> afterS
    uint64 afterS = 0;
    for(int i = 0; i < 8; i++)
    {
        // 每次取最低6位
        int t = (text << 58) >> 58;
        
        // x是t的高两位
        int x = t >> 4; 
        
        // y是t的低四位
        int y = (t << 2) >> 2;

        t = S_box[i][x][y];
        afterS = afterS | (t << (6 * i));

        // 右移6位
        text >> 6;
    }

    // 4. P-Perm
    return P_perm(afterS);
}
/* encryption
 * input : 64-bit key, 64-bit plainText
 * output: 64-bit cipherText
 */
uint64 encryption(uint64 key, uint64 plainText)
{
    // 0.generate subkeys 
    uint64 *subkeySet = (uint64 *) malloc(17 * sizeof(uint64));
    genSubKeys(key, subkeySet);

    // 1.IP perm -> L0R0(64-bit)
    uint64 L0R0 = initPerm(plainText);
    uint64 L[17], R[17];

    L[0] = L0R0 >> 32;
    R[0] = (L0R0 << 32) >> 32;

    // 2.Feistel rounds -> L16R16
    for(int i = 1; i <= 16; i++)
    {
        L[i] = R[i-1];
        R[i] = L[i-1] ^ Feistel(R[i-1], subkeySet[i]);
    }

    // 3.交换置换
    R[16] = R[16] << 32;
    uint64 ciphertext = R[16] | L[16];

    // 4.IP-1 perm
    ciphertext = finalPerm(ciphertext);

    return ciphertext;
}


/* decryption
 * input : 64-bit key, 64-bit cipherText
 * output: 64-bit plainText
 */
uint64 decryption(uint64 key, uint64 cipherText)
{
    
}
