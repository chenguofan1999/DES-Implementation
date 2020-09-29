// test random for 20 times
void randomTest()
{
    printf ("Start 20 random tests:\n\n");
    srand(time(NULL)); 

    for(int i = 0; i < 20; i++)
    {
        uint64 plain = 0;
        for(int j = 0; j < 64; j ++)
        {
            uint64 thisBit = rand() & 1;
            thisBit = thisBit << j;
            plain = plain | thisBit;
        }

        uint64 key = 0;
        for(int j = 0; j < 64; j ++)
        {
            uint64 thisBit = rand() & 1;
            thisBit = thisBit << j;
            key = key | thisBit;
        }

        uint64 cipher = encryption(key, plain);
        uint64 translated = decryption(key,cipher);
        
        printf("Encrypt : %016llx -> %016llx\n", plain, cipher);
        printf("Decrypt : %016llx -> %016llx\n", cipher, translated);

        if(plain == translated)
            printf("Check equal : %016llx == %016llx , succeed!\n",plain, translated);
        else printf("Check equal : %016llx != %016llx , failed!\n",plain, translated);
        printf("\n");
    }
}


void customTest()
{
    uint64 plain;
    uint64 key;
    while(1)
    {
        scanf("%16llx", &plain);
        scanf("%16llx", &key);
        uint64 cipher = encryption(key, plain);
        uint64 translated = decryption(key,cipher);
        printf("Encrypt : %016llx -> %016llx\n", plain, cipher);
        printf("Decrypt : %016llx -> %016llx\n", cipher, translated);
        if(plain == translated)
            printf("Check equal : %016llx == %016llx , succeed!\n",plain, translated);
        else printf("Check equal : %016llx != %016llx , failed!\n",plain, translated);
        printf("\n");
    }
}