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
        printf("%llu", num >> i & 1);
    printf("\n");
}