
typedef unsigned long long uint64;

/* Permutation function :
 * input : input block
 * table : table
 * fromN : number of bits before permutation
 * toN   : number of bits after permutation
 * [____|1,2,...,fromN] -> [___|1,2,...,toN] 
 */ 
uint64 perm(uint64 input, short table[], int fromN, int toN)
{
    uint64 ret = 0;
    for(int i = 0; i < toN; i++)
    {
        uint64 t = (input >> (fromN - table[i]) & 1);
        t = t << (toN - 1 - i);
        ret = ret | t;
    }
    return ret;
}

/* print format:
 * [decimal]
 * [binary]
 */
void printInBits(uint64 num)
{
    printf("%llu\n",num);
    for(int i = 63; i >= 0; i--)
        printf("%llu", num >> i & 1);
    printf("\n");
}

/* print format:
 * [decimal]
 * [highest 64 - n bits]  [lowest n bits] 
 */
void printInBitsN(uint64 num, int n)
{
    printf("%llu\n",num);
    for(int i = 63; i >= n; i--)
        printf("%llu", num >> i & 1);
    printf("  ");
    for(int i = n - 1; i >= 0; i--)
        printf("%llu", num >> i & 1);
    printf("\n");
}

