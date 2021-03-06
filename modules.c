#include "tables.c"
#include "toolFunc.c"


/* Initial Permutation
 * input : 64-bit plain text
 * output: 64-bit concatenation of L0 and R0
 */ 
uint64 initPerm(uint64 M)
{
    return perm(M, IP, 64, 64);
}

/* Final Permutation
 * input : 64-bit concatenation of R16 and L16
 * output: 64-bit cipher text
 */ 
uint64 finalPerm(uint64 M)
{
    return perm(M, FP, 64, 64);
}

/* E-Expansion
 * input : 32-bit R_i-1
 * output: 48-bit E(R_i-1)
 */ 
uint64 E_expansion(uint64 R)
{
    return perm(R, E, 32, 48);
}

/* PC1_perm in subkey generation
 * input : 64-bit key
 * output: 56-bit 
 */ 
uint64 PC1_perm(uint64 K64)
{
    return perm(K64, PC1, 64, 56);
}

/* PC1_perm in subkey generation
 * input : 56-bit
 * output: 48-bit 
 */ 
uint64 PC2_perm(uint64 K56)
{
    return perm(K56, PC2, 56, 48);
}

/* P_perm in Feistel func
 * input : 32-bit
 * output: 32-bit 
 */ 
uint64 P_perm(uint64 x)
{
    return perm(x, P, 32, 32);
}

/* generate subkeys
 * input : 64-bit key, array of subkeys
 * output: nothing but subkeys are writen
 */ 
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
        
        uint64 concat = (C[i] << 28) | D[i];
        subkeys[i] = PC2_perm(concat);
        
        
    }
}

/* Feistel round function
 * input : a 32-bit text and a 48-bit subkey
 * output: a 32-bit text
 */ 
uint64 Feistel(uint64 text, uint64 subkey)
{
    // 1. E-extension -> 48 bits
    text = E_expansion(text);

    // 2. Do Xor
    text = text ^ subkey;

    // 3. S-box transform -> afterS
    uint64 afterS = 0;
    for(int i = 0; i < 8; i++)
    {
        // take the lowest 6 bits
        uint64 t = (text << 58) >> 58;
        
        // x = t1t6
        uint64 x = (t >> 5) << 1 | (t & 1); 
        
        // y = t2t3t4t5
        uint64 y = t << 59 >> 59 >> 1;

        uint64 sOut = S_box[7 - i][x][y];
        sOut = sOut << (4 * i);
        afterS = afterS | sOut;

        text = text >> 6;
    }

    // 4. P-Perm
    uint64 res = P_perm(afterS);
    return res;
}


/* Encryption
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

    // 3.Exchange Perm
    R[16] = R[16] << 32;
    uint64 ciphertext = R[16] | L[16];

    // 4.IP-1 perm
    ciphertext = finalPerm(ciphertext);

    return ciphertext;
}

/* Decryption
 * input : 64-bit key, 64-bit cipherText
 * output: 64-bit plainText
 */
uint64 decryption(uint64 key, uint64 cipherText)
{
    // 0.generate subkeys 
    uint64 *subkeySet = (uint64 *) malloc(17 * sizeof(uint64));
    genSubKeys(key, subkeySet);

    // 1.IP perm -> L0R0(64-bit)
    uint64 L0R0 = initPerm(cipherText);
    uint64 L[17], R[17];

    L[0] = L0R0 >> 32;
    R[0] = (L0R0 << 32) >> 32;

    // 2.Feistel rounds -> L16R16
    for(int i = 1; i <= 16; i++)
    {
        L[i] = R[i-1];
        R[i] = L[i-1] ^ Feistel(R[i-1], subkeySet[17-i]);
    }

    // 3.Exchange Perm
    R[16] = R[16] << 32;
    uint64 plainText = R[16] | L[16];

    // 4.IP-1 perm
    plainText = finalPerm(plainText);

    return plainText;
}
