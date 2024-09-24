#include <stdio.h>
#include <string.h>

bool check(char* str, unsigned int len)
{
    if (len != 35)
        return false;
    for (int i = 0; i < len; i++)
    {
        str[i] ^= i;
        __asm
        {
            jz label1
            jnz label1
            _emit 0xe8
            label1:
        }
        str[i] += i;
    }
    unsigned __int8 enc[] = { 0x66,0x6e,0x65,0x67,0x83,0x7b,0x74,0x75,0x6b,0x71,0x6e,0x6f,0x73,0x6f,0x6e,0x6f,0x8b,0x8f,0x8e,0x8f,0x93,0x8f,0x93,0x8f,0x83,0x8a,0x8d,0x8a,0x99,0x90,0x88,0x9d,0x6e,0x21,0x81 };
    for (int i = 0; i < 35; i++)
        if ((unsigned __int8)str[i] != enc[i])
            return false;
    return true;
}

int main()
{
    char input[45] = { 0 };
    printf("I'm shikanokonoko.\n");
    printf("I made some changes to this program to make it hard to be decompiled.\n");
    printf("Now plz give me the flag!!:\n");
    scanf("%40s", input);
    __asm
    {
        jz label0
        jnz label0
        _emit 0xe8
        label0:
    }
    if (check(input, strlen(input)))
        printf("Correct!\n");
    else
        printf("Wrong!\n");
    return 0;
}//flag{shikanokonokonokokoshitantan!}