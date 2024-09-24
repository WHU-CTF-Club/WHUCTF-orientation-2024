#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char flag[45] = { 0 };
    printf("Welcome to your first reverse! Plz give me your flag:\n");
    scanf("%40s", flag);
    if (strncmp(flag, "flag{Welcome_to_", 16) != 0 || strlen(flag) != 38)
    {
        printf("Wrong flag!\n");
        return 0;
    }
    unsigned char enc1[22] = { 0x74,0x69,0x67,0x5c,0x73,0x6a,0x74,0x6b,0x6c,0x56,0x65,0x6d,0x53,0x5f,0x3d,0x79,0x75,0x63,0x61,0x76,0x35,0x68 };
    for (int i = 0; i < 22; i++)
    {
        if ((flag[16 + i] ^ i) != enc1[i])
        {
            printf("Wrong flag!\n");
            return 0;
        }
    }
    printf("Correct!\n");
    return 0;
}
//flag{Welcome_to_the_world_of_R3verse!}