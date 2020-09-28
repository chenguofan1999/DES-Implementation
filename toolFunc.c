typedef unsigned long long uint64;
uint64 perm(uint64 input, short table[], int n)
{
    uint64 ret = 0;
    for(int i = 0; i < n; i++)
    {
        uint64 t = (input >> (64 - table[i]) & 1);
        t = t << (n - 1 - i);
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

// 低n位
void print64n(uint64 num, int n)
{
    printf("%llu\n",num);
    for(int i = 63; i >= n; i--)
        printf("%llu", num >> i & 1);
    printf("  ");
    for(int i = n - 1; i >= 0; i--)
        printf("%llu", num >> i & 1);
    printf("\n");
}