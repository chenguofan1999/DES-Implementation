#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "modules.c"
#include "tests.c"


int main()
{
    /* Random test:
     * The system automatically generate 20 pairs of plain texts and keys
     * For each pair,
     * 1. show the Encryption and Decryption result
     * 2. Check if the decrypted text equals the original plain text
     */ 
    randomTest();

    /* Custom test (Activate it if you want to):
     * Type in two 64-bit integer in hexadecimal (length = 16), 
     * first of which is the plain text
     * second of which is the key
     * For each pair of input,
     * 1. show the Encryption and Decryption result
     * 2. Check if the decrypted text equals the original plain text
     */
    //customTest();
}