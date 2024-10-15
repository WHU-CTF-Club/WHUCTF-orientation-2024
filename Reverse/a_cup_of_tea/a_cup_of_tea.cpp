#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DELTA 0x9e3779b9

void tea_encrypt(unsigned int* text, unsigned int* key)
{
    unsigned int v0 = text[0];
    unsigned int v1 = text[1];
    unsigned int sum = 0;
    for (int i = 0;i < 32;i++)
    {
        sum += DELTA;
        v0 += ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]) ^ 0x114514;
        v1 += ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]) ^ 0x1919810;
    }
    text[0] = v0;
    text[1] = v1;
}

int main()
{
    char input[45] = { 0 };
    char key[] = "SiestazzSiestazz";
    int len = 0;
    printf("Plz input your flag:\n");
    scanf("%40s", input);
    len = strlen(input);
    if (len != 31)
    {
        printf("Wrong length!\n");
        exit(0);
    }
    for (int i = 0; i < len; i += 8)
        tea_encrypt((unsigned int*)(input + i), (unsigned int*)key);
    unsigned char enc[] = { 0x78,0x2c,0xc6,0xa5,0x1c,0x78,0x5d,0x8c,0xeb,0xaa,0xd4,0x8d,0x3c,0x31,0xef,0xae,0xa8,0xaa,0x14,0x2c,0xd8,0x6f,0x8,0xd2,0x20,0x62,0xe1,0xd0,0x68,0xad,0x3a,0xd8 };

    for (int i = 0;i < 32;i++)
        if ((unsigned char)input[i] != enc[i])
        {
            printf("Wrong flag!\n");
            exit(0);
        }
    printf("Your flag is correct!\n");
    return 0;
}//flag{let's_hav3_A_cup_0f_T3A!!}
